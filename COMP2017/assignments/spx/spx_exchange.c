/**
 * comp2017 - assignment 3
 * Dylan Herdan
 * 500468777
 */

#include "spx_exchange.h"

sigdata_t* spx_sig_head = NULL;
sigdata_t* spx_sig_tail = NULL;

void sig_handler(int signo, siginfo_t* sinfo, void* context)
{
    sigdata_t* sigdata = malloc(sizeof(sigdata_t));
    sigdata->source_pid = sinfo->si_pid;
    sigdata->signo = signo;
    sigdata->next = NULL;

    if (NULL == spx_sig_head)
    {
        spx_sig_head = sigdata;
        spx_sig_tail = sigdata;
    }

    else
    {
        spx_sig_tail->next = sigdata;
        spx_sig_tail = sigdata;
    }

}


#ifndef TESTING
int main(int argc, char **argv) 
{
    //check command line args
    if (argc < 2)
    {
        perror("Not enough args");
        return 1;
    }

    //startup - read product file
    printf("[SPX] Starting\n");

    char* product_file = argv[1];
    orderbook_t* orderbook = get_products(product_file);

    if (NULL == orderbook)
        return 1;
    
    printf("[SPX] Trading %d products:", orderbook->num_products);
    
    for(int i = 0; i < orderbook->num_products; i++)
    {
        printf(" %s", orderbook->products[i].name);
    }
    printf("\n");

    //set up signals
    struct sigaction sig;
    memset(&sig, 0, sizeof(struct sigaction));
    sig.sa_sigaction = sig_handler; //SETS Handler
    sig.sa_flags = SA_SIGINFO | SA_RESTART;
    
    if(sigaction(SIGUSR1, &sig, NULL) == -1) 
    {
        perror("sigaction failed");
        return 1;
    }
    if(sigaction(SIGCHLD, &sig, NULL) == -1) 
    {
        perror("sigaction failed");
        return 1;
    }

    //set up pipes
    int num_traders = argc - 2;

    if (!check_files(argc, argv))
    {
        clear_orderbook(orderbook);
        free(orderbook->products);
        free(orderbook);
        return 1;
    }

    trader_t* traders = init_traders(num_traders, argv, orderbook);
    if (NULL == traders)
        return 1;
    run_market(orderbook, traders, num_traders);

    for(int i = 0; i < num_traders; i++)
    {
        //printf("closing trader %d\n", traders[i].trader_id);
        unlink(traders[i].fifo_etot);
        unlink(traders[i].fifo_ttoe);
        close(traders[i].fd_read);
        close(traders[i].fd_write);
        free(traders[i].inventory);
    }

    printf("[SPX] Trading completed\n");
    printf("[SPX] Exchange fees collected: $%lli\n", orderbook->fees);

    free(traders);
    clear_orderbook(orderbook);
    free(orderbook->products);
    free(orderbook);
    return 0;
}
#endif

bool check_files(int argc, char** argv)
{
    for(int i = 2; i < argc; i++)
    {
        if(-1 == access(argv[i], F_OK))
        {    
            perror("error opening files");
            return false;
        }
    }
    return true;
}

trader_t* init_traders(int num_traders, char** argv, orderbook_t* ob)
{
    //init trader
    trader_t* traders = malloc(sizeof(trader_t) * num_traders);
    for(int i = 0; i < num_traders; i++){
        traders[i].trader_id = i;
        traders[i].status = INIT;
        traders[i].num_orders = 0;


        traders[i].inventory = malloc(sizeof(stock_t) * ob->num_products);

        for (int j = 0; j < ob->num_products; j++)
        {
            strncpy(traders[i].inventory[j].name, ob->products[j].name, PROD_LEN);
            traders[i].inventory[j].num = 0;
            traders[i].inventory[j].value = 0;
        }


        sprintf(traders[i].fifo_etot, FIFO_EXCHANGE, traders[i].trader_id);
        sprintf(traders[i].fifo_ttoe, FIFO_TRADER, traders[i].trader_id);

        //open fifos
        if(0 > mkfifo(traders[i].fifo_etot, S_IRWXU | S_IRWXG))
        {
            perror("cant open pipe");
        }
        else
        {
            printf("[SPX] Created FIFO %s\n", traders[i].fifo_etot);
        }

        if(0 > mkfifo(traders[i].fifo_ttoe, S_IRWXU | S_IRWXG))
        {
            perror("cant open pipe");
        }
        else
        {
            printf("[SPX] Created FIFO %s\n", traders[i].fifo_ttoe);
        }
        
        //fork process and launch trader
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("unable to fork");
            return NULL;
        }

        char id_str[ID_SZ];
        sprintf(id_str, "%d", traders[i].trader_id);        
        //child - launch trader
        if (0 == pid)
        {
            
            if (execl(argv[i + 2], argv[i + 2], id_str, NULL) == -1)
            {
                perror("exec failed");
                return NULL;
            }
        }

        //parent - finish initialisation of trader
        else
        {
            
            printf("[SPX] Starting trader %s (%s)\n", id_str, argv[i + 2]);
            // connect to named pipes
            traders[i].pid = pid;
            
            traders[i].fd_write = open(traders[i].fifo_etot, O_WRONLY);
            if (traders[i].fd_write < 0)
            {
                perror("parent unable to open write pipe");
                return NULL;
            }
            fcntl(traders[i].fd_write, F_SETFL, O_NONBLOCK);

            printf("[SPX] Connected to %s\n", traders[i].fifo_etot);

            traders[i].fd_read = open(traders[i].fifo_ttoe, O_RDONLY);
            if (traders[i].fd_read < 0)
            {
                perror("parent unable to open read pipe");
                return NULL;
            }
            printf("[SPX] Connected to %s\n", traders[i].fifo_ttoe);
            

            traders[i].status = OPEN;

        }
    }
	return traders;
}

orderbook_t* get_products(char* filename)
{
    FILE* product_file = fopen(filename, "r");
    if(NULL == product_file)
    {
        perror("error opening product file");
        return NULL;
    }

    orderbook_t* orderbook = malloc(sizeof(orderbook_t));
    orderbook->num_products = -1;
    orderbook->products = NULL;
    orderbook->fees = 0;


    char buf[BUF_SZ] = {0};
    fgets(buf, BUF_SZ, product_file);
    sscanf(buf, "%d", &(orderbook->num_products));
    orderbook->products = malloc(sizeof(product_t) * orderbook->num_products);
    int i = 0;


    while ( (i < orderbook->num_products) && 
        (NULL != fgets(buf, PROD_LEN, product_file)) )
    {
        if ('\n' == buf[strlen(buf) - 1])
            buf[strlen(buf) - 1] = '\0';
        if ( 0 < strlen(buf))
        {
            strncpy(orderbook->products[i].name, buf, PROD_LEN);
            orderbook->products[i].orders = NULL;
            orderbook->products[i].buy_orders = NULL;
            orderbook->products[i].sell_orders = NULL;
            orderbook->products[i].buy_levels = 0;
            orderbook->products[i].sell_levels = 0;
            i++;
        }
        memset(buf, 0, BUF_SZ);
    }

    if (i < orderbook->num_products)
    {
        free(orderbook->products);
        free(orderbook);
        return NULL;
    }

    return orderbook;
}   

void run_market(orderbook_t* ob, trader_t* traders, int num_traders)
{
    int current_traders = num_traders;
    
    //open market
    char buf[BUF_SZ];
    char* alert = "MARKET OPEN;";
    strncpy(buf, alert, strlen(alert));

    for(int i = 0; i < num_traders; i++)
    {
        write(traders[i].fd_write, alert, strlen(alert));
        kill(traders[i].pid, SIGUSR1);
    }

    int counter = 0;     

    while (current_traders || spx_sig_head != NULL)
    {
        //wait for signal
        if (NULL == spx_sig_head)
        {
            pause();
        }

        int id = -1;

        for(int i = 0; i < num_traders; i++)
        {
            if (traders[i].pid == spx_sig_head->source_pid)
            {
                id = i;
                break;
            }
        }

        if (0 > id)
        {
            perror("unknown signal origin");
        }


        trader_t* trader = &traders[id];

        if (SIGUSR1 == spx_sig_head->signo)
        {
            struct pollfd fds[1];
            fds[0].fd = trader->fd_read;
            fds[0].events = 0;
            fds[0].events |= POLLIN;

            poll(fds, 1, 0);

            //if (!(fds[0].revents & POLLERR) && !(fds[0].revents & POLLHUP))
            if (fds[0].revents & POLLIN && 0 < strlen(buf))
            {
                memset(buf, 0, BUF_SZ);
                read(trader->fd_read, buf, BUF_SZ);
                //bool terminator = false;
                if (0 < strlen(buf))
                {
                    if (buf[strlen(buf) - 1] == ';')
                    {
                        buf[strlen(buf) - 1] = 0;
                        //terminator = true;
                    }

                    printf("[SPX] [T%d] Parsing command: ", trader->trader_id);
                    printf("<%s>\n", buf);
                }
            }

                


            if (make_order(buf, ob, traders, num_traders, id, counter))
            {
                match_orders(ob, traders, num_traders);
                print_orderbook(ob);
                print_positions(traders, num_traders, ob->num_products);
            }

        }

        else if (SIGCHLD == spx_sig_head->signo)
        {
            //close trader
            trader->status = CLOSED;
            printf("[SPX] Trader %d disconnected\n", id);
            current_traders--;
        }

        sigdata_t* temp = spx_sig_head->next;        

        free(spx_sig_head);

        spx_sig_head = temp;

        if (NULL == spx_sig_head)
        {
            spx_sig_tail = NULL;
        }

        counter++;
    }
}

bool make_order(
    char* order_str, 
    orderbook_t* ob, 
    trader_t* traders, 
    int num_traders, 
    int sender, 
    int counter
    )
{
    char* new_order = strdup(order_str);
    char* order_type = strsep(&new_order, " ");
    char general[BUF_SZ];
    char specific[BUF_SZ];
    bool valid;

    //printf(DEBUG, order_type);

    if (0 == strncasecmp("BUY", order_type, strlen("BUY") + 1))
    {
        order_t* order = make_buy(ob, new_order, sender, traders);
        if (NULL != order)
        {
            valid = true;
            order->time = counter;
            sprintf(specific, "%s %d;", "ACCEPTED", order->id);
            sprintf(general, "MARKET BUY %s %d %d;", 
                order->product, 
                order->qty, 
                order->price);
            
            notify(traders, num_traders, general, sender, specific);

        }
        else
        {
            valid = false;
            char* msg = "INVALID;";
            write(traders[sender].fd_write, msg, strlen(msg));
            kill(traders[sender].pid, SIGUSR1);
        }

    }

    else if (0 == strncasecmp("SELL", order_type, strlen("SELL") + 1))
    {
        order_t* order = make_sell(ob, new_order, sender, traders);
        if (NULL != order)
        {
            order->time = counter;
            valid = true;
            sprintf(specific, "%s %d;", "ACCEPTED", order->id);
            sprintf(general, "MARKET SELL %s %d %d;", 
                order->product, 
                order->qty, 
                order->price);
            notify(traders, num_traders, general, sender, specific);
        }
        else
        {
            valid = false;
            char* msg = "INVALID;";
            write(traders[sender].fd_write, msg, strlen(msg));
            kill(traders[sender].pid, SIGUSR1);
        }
    }

    else if (0 == strncasecmp("AMEND", order_type, strlen("amend") + 1))
    {
        order_t* order = amend_order(ob, new_order, sender, counter);
        if (NULL != order)
        {
            valid = true;
            sprintf(specific, "%s %d;", "AMENDED", order->id);
            char* type_str = (order->type == BUY) ? "BUY" : "SELL";
            sprintf(general, "MARKET %s %s %d %d;", 
                type_str, 
                order->product, 
                order->qty, 
                order->price);
            notify(traders, num_traders, general, sender, specific);
        }
        else
        {
            valid = false;
            char* msg = "INVALID;";
            write(traders[sender].fd_write, msg, strlen(msg));
            kill(traders[sender].pid, SIGUSR1);
        }    
    }

    else if (0 == strncasecmp("CANCEL", order_type, strlen("CANCEL") + 1))
    {
        order_t* order = cancel_order(ob, new_order, sender);
        if (NULL != order)
        {
            valid = true;
            sprintf(specific, "%s %d;", "CANCELLED", order->id);
            char* type_str = (order->type == BUY) ? "BUY" : "SELL";
            sprintf(general, "MARKET %s %s %d %d;", 
                type_str, 
                order->product, 
                order->qty, 
                order->price);
            int prod_index = find_product(ob, order->product);
            product_t* product = &ob->products[prod_index];
            
            if (BUY == order->type)
                product->buy_levels--;
            else
                product->sell_levels--;

            free_order(product, order);
            notify(traders, num_traders, general, sender, specific);
        }
        else
        {
            valid = false;
            char* msg = "INVALID;";
            write(traders[sender].fd_write, msg, strlen(msg));
            kill(traders[sender].pid, SIGUSR1);
        }     
    }

    else
    {
        char* msg = "INVALID;";
        write(traders[sender].fd_write, msg, strlen(msg));
        kill(traders[sender].pid, SIGUSR1);
        free(order_type);
        //free(order);
        return false;
    }

    free(order_type);
    return valid;
}

order_t* make_buy(orderbook_t* ob, char* str, int sender, trader_t* traders)
{
    if (3 > strcount(str, ' '))
        return NULL;
    
    type_t type = BUY;
    
    //duplicate string
    char* order_str = strdup(str);
    
    //get order ID
    char* id_str = strsep(&order_str, " ");
    if ( (NULL == id_str) 
        || (!is_num(id_str)) 
        || (traders[sender].num_orders != atoi(id_str)) )
    {
        free(id_str);
        return NULL;
    }

    int id = atoi(id_str);

    //get product
    char* prod = strsep(&order_str, " ");
    if ( (NULL == prod) || ( 0 > find_product(ob, prod)) )
    {
        free(id_str);
        return NULL;
    }
    int prod_index = find_product(ob, prod);


    //get order quantity
    char* qty_str = strsep(&order_str, " ");
    if ( (NULL == qty_str) || (!is_num(qty_str)) )
    {
        free(id_str);
        return NULL;
    }
    int qty = atoi(qty_str);

    if ( (1 > qty) || (999999 < qty))
    {
        free(id_str);
        return NULL;
    }

    //get order price
    char* price_str = strsep(&order_str, " ");
    if ( (NULL == price_str) || (!is_num(price_str)) )
    {
        free(id_str);
        return NULL;
    }

    int price = atoi(price_str);

    if ( (1 > price) || (999999 < price))
    {
        free(id_str);
        return NULL;
    }

    traders[sender].num_orders++;

    order_t* order = malloc(sizeof(order_t));
    order->type = type;
    strncpy(order->product, prod, PROD_LEN);
    order->cancelled = false;
    order->id = id;
    order->qty = qty;
    order->price = price;
    order->next = NULL;
    order->prev = NULL;
    order->type_next = NULL;
    order->type_prev = NULL;
    order->sender = sender;


    ob->products[prod_index].buy_levels++;


    if (1 == ob->products[prod_index].buy_levels)
    {
        ob->products[prod_index].buy_orders = order;
    }
    else
    {
        int i = 1;
        order_t* cursor = ob->products[prod_index].buy_orders;
        order_t* temp = NULL;
        while ((i < ob->products[prod_index].buy_levels) && 
            (order->price <= cursor->price))
        {
            i++;
            temp = cursor;
            cursor = cursor->type_next;    
        }

        if (NULL == temp)
        {
            //insert at beginning
            ob->products[prod_index].buy_orders = order;
            cursor->type_prev = order;
            order->type_next = cursor;
        }

        else if (ob->products[prod_index].buy_levels == i)
        {
            //insert at end
            temp->type_next = order;
            order->type_prev = temp;
        }

        else
        {
            //middle of list
            cursor->type_prev->type_next = order;
            order->type_prev = cursor->type_prev;
            order->type_next = cursor;
            cursor->type_prev = order;
        }
    }

    free(id_str);
    return order;

}

order_t* make_sell(orderbook_t* ob, char* str, int sender, trader_t* traders)
{
    if (3 > strcount(str, ' '))
        return NULL;
    
    type_t type = SELL;
    
    //duplicate string
    char* order_str = strdup(str);
    
    //get order ID
    char* id_str = strsep(&order_str, " ");
    if ( (NULL == id_str) 
        || (!is_num(id_str)) 
        || (traders[sender].num_orders != atoi(id_str)) )
    {
        free(id_str);
        return NULL;
    }

    int id = atoi(id_str);

    //get product
    char* prod = strsep(&order_str, " ");
    if ( (NULL == prod) || ( 0 > find_product(ob, prod)) )
    {
        free(id_str);
        return NULL;
    }
    int prod_index = find_product(ob, prod);


    //get order quantity
    char* qty_str = strsep(&order_str, " ");
    if ( (NULL == qty_str) || (!is_num(qty_str)) )
    {
        free(id_str);
        return NULL;
    }
    int qty = atoi(qty_str);

    if ( (1 > qty) || (999999 < qty))
    {
        free(id_str);
        return NULL;
    }

    //get order price
    char* price_str = strsep(&order_str, " ");
    if ( (NULL == price_str) || (!is_num(price_str)) )
    {
        free(id_str);
        return NULL;
    }

    int price = atoi(price_str);

    if ( (1 > price) || (999999 < price))
    {
        free(id_str);
        return NULL;
    }

    traders[sender].num_orders++;

    order_t* order = malloc(sizeof(order_t));
    order->type = type;
    strncpy(order->product, prod, PROD_LEN);
    order->cancelled = false;
    order->id = id;
    order->qty = qty;
    order->price = price;
    order->next = NULL;
    order->prev = NULL;
    order->type_next = NULL;
    order->type_prev = NULL;
    order->sender = sender;


    ob->products[prod_index].sell_levels++;


    if (1 == ob->products[prod_index].sell_levels)
    {
        ob->products[prod_index].sell_orders = order;
    }
    else
    {   
        int i = 1;
        order_t* cursor = ob->products[prod_index].sell_orders;
        order_t* temp = NULL;
        while ((i < ob->products[prod_index].sell_levels) && 
            (order->price >= cursor->price))
        { 
            i++;
            temp = cursor;
            cursor = cursor->type_next;    
        }
       
        if (NULL == temp)
        {
            //insert at beginning
            ob->products[prod_index].sell_orders = order;
            cursor->type_prev = order;
            order->type_next = cursor;
        }

        else if (ob->products[prod_index].sell_levels == i)
        {
            //insert at end
            temp->type_next = order;
            order->type_prev = temp;
            // cursor->type_next = order;
            // order->type_prev = cursor;
        }

        else
        {
            //middle of list
            cursor->type_prev->type_next = order;
            order->type_prev = cursor->type_prev;
            order->type_next = cursor;
            cursor->type_prev = order;
        }
    }

    free(id_str);
    return order;
}

void print_orderbook(orderbook_t* ob)
{
    printf("[SPX]\t--ORDERBOOK--\n");
    for (int i = 0; i < ob->num_products; i++)
    {
        product_t product = ob->products[i];

        int buy_levels = 0;
        int last = -1;
        order_t* cursor = product.buy_orders;

        for (int j = 0; j < product.buy_levels; j++)
        {
            if(last != cursor->price)
                buy_levels++;
            last = cursor->price;
            cursor = cursor->type_next;
        }

        int sell_levels = 0;
        last = -1;
        cursor = product.sell_orders;

        for (int j = 0; j < product.sell_levels; j++)
        {
            if(last != cursor->price)
                sell_levels++;
            last = cursor->price;
            cursor = cursor->type_next;
        }


        printf("[SPX]\tProduct: %s; ", product.name);
        printf("Buy levels: %d; Sell levels: %d\n", buy_levels, sell_levels);

        order_t* buy_cursor = product.buy_orders;        
        order_t* sell_cursor = product.sell_orders;
        for (int j = 1; j < product.sell_levels; j++)
        {
            sell_cursor = sell_cursor->type_next;
        }
        
        while ( (NULL != sell_cursor) || (NULL != buy_cursor) )
        {
            bool print_buy;
            if (sell_cursor == NULL)
                print_buy = true;
            else if (NULL == buy_cursor)
                print_buy = false;
            else if (buy_cursor->price > sell_cursor->price)
                print_buy = true;
            else
                print_buy = false;

            if (print_buy)
            {
                int count = 0;
                int total = 0;
                bool same = true;

                while (same)
                {
                    count++;
                    total += buy_cursor->qty;

                    if (NULL == buy_cursor->type_next)
                        same = false;
                    else if (buy_cursor->price != buy_cursor->type_next->price)
                        same = false;
                    else
                        buy_cursor = buy_cursor->type_next;                    
                }

                char* type = "BUY";
                char* str = (1 == count) ? "order" : "orders";
                printf("[SPX]\t\t%s %d @ $%d (%d %s)\n", 
                    type, 
                    total, 
                    buy_cursor->price, 
                    count, 
                    str);
                buy_cursor = buy_cursor->type_next;
            }
            else
            {
                int count = 0;
                int total = 0;
                bool same = true;

                while (same)
                {
                    count++;
                    total += sell_cursor->qty;

                    if (NULL == sell_cursor->type_prev)
                        same = false;
                    else if (sell_cursor->price != sell_cursor->type_prev->price)
                        same = false;
                    else
                        sell_cursor = sell_cursor->type_prev;                    
                }
                char* type = "SELL";
                char* str = (1 == count) ? "order" : "orders";
                printf("[SPX]\t\t%s %d @ $%d (%d %s)\n", 
                    type, 
                    total, 
                    sell_cursor->price, 
                    count, 
                    str);
                sell_cursor = sell_cursor->type_prev;
            }     
        }    
    }
}

void print_positions(trader_t* traders, int num_traders, int num_products)
{
    printf("[SPX]\t--POSITIONS--\n");

    for (int i = 0; i < num_traders; i++)
    {
        printf("[SPX]\tTrader %d:", traders[i].trader_id);

        for (int j = 0; j < num_products; j++)
        {
            stock_t product = traders[i].inventory[j];
            printf(" %s %d ($%lli)", product.name, product.num, product.value);
            if (num_products - 1 != j)
                printf(",");
        }

        printf("\n");
    }
}

bool is_num(char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

int find_product(orderbook_t* ob, char* str)
{
    for(int i = 0; i < ob->num_products; i++)
    {
        product_t prod = ob->products[i];
        if (0 == strncasecmp(prod.name, str, PROD_LEN))
            return i;
    }
    return -1;
}


void clear_orderbook(orderbook_t* ob)
{
    for (int i = 0; i < ob->num_products; i++)
    {
        product_t product = ob->products[i];

        order_t* cursor = product.buy_orders;

        while (NULL != cursor)
        {
            order_t* temp = cursor;
            cursor = cursor->type_next;
            free(temp);
        }

        cursor = product.sell_orders;

        while (NULL != cursor)
        {
            order_t* temp = cursor;
            cursor = cursor->type_next;
            free(temp);
        }
    }
}

/*
 *notify
 *notifies all traders with msg except trader tid which is sent i_msg
 *
 *trader_t* traders:: array of traders to notify
 *int num_traders:: total number of traders
 *char* msg:: message to send to traders
 *int tid:: trader to get individual message
 *      if less than 0 or greater than num_traders all will recieve same message
 *char* new_msg:: message to send to trader tid
 * 
 *returns nothing
 */
void notify(trader_t* traders, int num_traders, char* msg, int tid, char* new_msg)
{
    // printf(DEBUG, "notify");
    for (int i = 0; i < num_traders; i++)
    {
        trader_t trader = traders[i];
        if ( (tid == i) && (OPEN == trader.status) )
        {
            // printf("sending trader %d %s\n", i, new_msg);
            write(trader.fd_write, new_msg, strlen(new_msg));
        }
        else if (OPEN == trader.status)
        {
            // printf("sending trader %d %s\n", i, msg);
            write(trader.fd_write, msg, strlen(msg));
        }
        // printf(DEBUG, "KILLING");
        kill(trader.pid, SIGUSR1);
    }
    // printf(DEBUG, "notified");
}

void match_orders(orderbook_t* ob, trader_t* traders, int num_traders)
{
    for (int i = 0; i < ob->num_products; i++)
    {
        product_t* product = &(ob->products[i]);


        order_t* buy_cursor = product->buy_orders;
        order_t* sell_cursor = product->sell_orders;
            

        while ( (NULL != sell_cursor) && 
            (NULL != buy_cursor) && 
            (buy_cursor->price >= sell_cursor->price) )
        {

            //match sale
            int qty;
            int cost;
            if (buy_cursor->time < sell_cursor->time)
                cost = buy_cursor->price;
            else
                cost = sell_cursor->price;

            int to_free = 0;
            order_t* free_orders[NUM_CURSORS];
            order_t* next_buy = buy_cursor;
            order_t* next_sell = sell_cursor;

            if (buy_cursor->qty > sell_cursor->qty)
            {
                buy_cursor->qty -= sell_cursor->qty;
                qty = sell_cursor->qty;
                free_orders[to_free] = sell_cursor;
                to_free++; 
                next_sell = sell_cursor->type_next; 
                product->sell_levels--;  
            }

            else if (buy_cursor->qty < sell_cursor->qty)
            {
                sell_cursor->qty -= buy_cursor->qty;
                qty = buy_cursor->qty;
                free_orders[to_free] = buy_cursor;
                to_free++;
                next_buy = buy_cursor->type_next;
                product->buy_levels--;
            }

            else
            {
                qty = buy_cursor->qty;
                free_orders[to_free] = sell_cursor;
                to_free++;
                free_orders[to_free] = buy_cursor;
                to_free++;
                next_sell = sell_cursor->type_next;
                next_buy = buy_cursor->type_next;
                product->sell_levels--;
                product->buy_levels--;
            }

            //calculate fee and update trader inventory
            long long total = (long long)qty * (long long)cost;
            long long fee = round_float((double)total * FEE_PERCENTAGE);
            if (buy_cursor->time < sell_cursor->time)
            {
                //fee to seller
                stock_t* buy_stock = &traders[buy_cursor->sender].inventory[i];
                stock_t* sell_stock = &traders[sell_cursor->sender].inventory[i];

                buy_stock->num += qty;
                buy_stock->value -= total;

                sell_stock->num -= qty;
                sell_stock->value += (total - fee);
                printf("[SPX] Match: Order %d [T%d], ", 
                    buy_cursor->id, 
                    buy_cursor->sender);
                printf("New Order %d [T%d], ", 
                    sell_cursor->id, 
                    sell_cursor->sender);
                printf("value: $%lli, fee: $%lli.\n", total, fee);

            }
            else
            {
                //fee to buyer
                stock_t* buy_stock = &traders[buy_cursor->sender].inventory[i];
                stock_t* sell_stock = &traders[sell_cursor->sender].inventory[i];

                buy_stock->num += qty;
                buy_stock->value -= (total + fee);

                sell_stock->num -= qty;
                sell_stock->value += total;
                printf("[SPX] Match: Order %d [T%d], ", 
                    sell_cursor->id, 
                    sell_cursor->sender);
                printf("New Order %d [T%d], ", 
                    buy_cursor->id, 
                    buy_cursor->sender);
                printf("value: $%lli, fee: $%lli.\n", total, fee);
            }

            //notify traders
            char buf[BUF_SZ];

            struct pollfd fds[NUM_CURSORS];
            fds[0].fd = traders[buy_cursor->sender].fd_write;
            fds[0].events = 0;
            //fds[0].events |= POLLIN;

            fds[1].fd = traders[sell_cursor->sender].fd_write;
            fds[1].events = 0;
            //fds[1].events |= POLLIN;

            int timeout = 1;

            poll(fds, NUM_CURSORS, timeout);


            if (!(fds[0].revents & POLLERR) && !(fds[0].revents & POLLHUP))
            {
                int write_size = sprintf(buf, "FILL %d %d;", buy_cursor->id, qty);
                write(traders[buy_cursor->sender].fd_write, buf, write_size);
                kill(traders[buy_cursor->sender].pid, SIGUSR1);
            }


            if (!(fds[1].revents & POLLERR) && !(fds[1].revents & POLLHUP))
            {
                int write_size = sprintf(buf, "FILL %d %d;", sell_cursor->id, qty);
                write(traders[sell_cursor->sender].fd_write, buf, write_size);
                kill(traders[sell_cursor->sender].pid, SIGUSR1);    
            }
            
            for (int j = 0; j < to_free; j++)
            {
                free_order(product, free_orders[j]);
            }

            buy_cursor = next_buy;
            sell_cursor = next_sell;

            ob->fees += fee;
        }

    }
}

long long round_float(double x)
{
    if ((x - (long long)x) < 0.5)
        return (long long)x;
    else
        return (long long)x + 1;
}

void free_order(product_t* product, order_t* order)
{

    //rearrange typed orders
    if (NULL == order->type_prev) //first entry
    {
        if (order->type == BUY)
            product->buy_orders = order->type_next;
        else if (order->type == SELL)
            product->sell_orders = order->type_next;
        
        if (NULL != order->type_next)
        {
            order->type_next->type_prev = NULL;
        }
    }

    else //prev entry exists
    {
        if (NULL != order->type_next) //middle entry
        {
            order->type_next->type_prev = order->type_prev;
            order->type_prev->type_next = order->type_next;
        } 
        else //last entry
        {
            order->type_prev->type_next = NULL;
        }
    } 

    free(order);
}

order_t* amend_order(orderbook_t* ob, char* str, int sender, int counter)
{    
    //duplicate string
    if (2 > strcount(str, ' '))
        return NULL;
    
    char* order_str = strdup(str);
    
    //get order ID
    char* id_str = strsep(&order_str, " ");
    if ( (NULL == id_str) || (!is_num(id_str)) )
    {
        free(id_str);
        return NULL;
    }

    int id = atoi(id_str);

    //get order quantity
    char* qty_str = strsep(&order_str, " ");
    if ( (NULL == qty_str) || (!is_num(qty_str)) )
    {
        free(id_str);
        return NULL;
    }
    int qty = atoi(qty_str);

    if ( (1 > qty) || (999999 < qty))
    {
        free(id_str);
        return NULL;
    }

    //get order price
    char* price_str = strsep(&order_str, " ");
    if ( (NULL == price_str) || (!is_num(price_str)) )
    {
        free(id_str);
        return NULL;
    }

    int price = atoi(price_str);
    if ( (1 > price) || (999999 < price))
    {
        free(id_str);
        return NULL;
    }


    order_t* order = NULL;
    bool found = false;
    int i = 0;

    while (!found && (i < ob->num_products) )
    {
        product_t* product = &ob->products[i];

        order_t* cursor = product->buy_orders;
        while ( (NULL != cursor) && (!found) )
        {
            if ( (cursor->id == id) && (cursor->sender == sender) )
            {
                found = true;
                order = cursor;
            }
            cursor = cursor->type_next;
        }
        
        cursor = product->sell_orders;
        while ( (NULL != cursor) && (!found) )
        {
            if ( (cursor->id == id) && (cursor->sender == sender) )
            {
                found = true;
                order = cursor;
            }
            cursor = cursor->type_next;
        }


        i++;
    }

    if (found)
    {
        order->qty = qty;
        order->price = price;
        order->time = counter;
        product_t* prod = &ob->products[find_product(ob, order->product)];
        move_order(prod, order);
    }

    free(id_str);
    return order;
}

order_t* cancel_order(orderbook_t* ob, char* str, int sender)
{   
    if (NULL == str)
        return false;
         
    //duplicate string    
    char* order_str = strdup(str);
    
    //get order ID
    char* id_str = strsep(&order_str, " ");
    if ( (NULL == id_str) || (!is_num(id_str)) )
    {
        free(id_str);
        return NULL;
    }

    int id = atoi(id_str);
    
    order_t* order = NULL;
    bool found = false;
    int i = 0;

    while (!found && (i < ob->num_products) )
    {
        product_t* product = &ob->products[i];

        order_t* cursor = product->buy_orders;
        while ( (NULL != cursor) && (!found) )
        {
            if ( (cursor->id == id) && (cursor->sender == sender) )
            {
                found = true;
                order = cursor;
            }
            cursor = cursor->type_next;
        }
        
        cursor = product->sell_orders;
        while ( (NULL != cursor) && (!found) )
        {
            if ( (cursor->id == id) && (cursor->sender == sender) )
            {
                found = true;
                order = cursor;
            }
            cursor = cursor->type_next;
        }


        i++;
    }

    if (found)
    {
        order->qty = 0;
        order->price = 0;
    }
    free(id_str);
    return order;

}

int strcount(char* str, char delim)
{
    if (NULL == str)
        return 0;
    int i = 0;
    int count =0;
    while ('\0' != str[i])
    {
        i++;
        if (str[i] == delim)
            count++;
    }
    return count;
}

void move_order(product_t* product, order_t* order)
{
    //remove order from list
    if (order->type_prev == NULL) // first
    {
        if (NULL == order->type_next)
            return;
        else
        {
            if (BUY == order->type)
                product->buy_orders = order->type_next;
            else
                product->sell_orders = order->type_next;
            order->type_next->type_prev = NULL;
        }
    }

    else
    {
        if (NULL == order->type_next) // last
        {
            order->type_prev->type_next = NULL;
        }

        else // middle
        {
            order->type_next->type_prev = order->type_prev;
            order->type_prev->type_next = order->type_next;
        }
    }

    //insert back in correct location

    int count = 1;
    bool loc = false;
    order_t* cursor;
    order_t* prev = NULL;
    
    if (BUY == order->type)
    {
        if (1 == product->buy_levels)
            return;
        cursor = product->buy_orders;
        while ((cursor != NULL) && !loc)
        {
            if (cursor->price > order->price)
            {
                prev = cursor;
                cursor = cursor->type_next;
                count++;
            } 

            else if ( (cursor->price == order->price) && 
                (cursor->time < order->time) )
            {
                prev = cursor;
                cursor = cursor->type_next;
                count++;
            }

            else
            {
                loc = true;
            }
        }

        if (1 == count) //should be first
        {
            product->buy_orders->type_prev = order;
            order->type_next = product->buy_orders;
            order->type_prev = NULL;
            product->buy_orders = order;
        }

        else if (!loc) // should be last
        {
            prev->type_next = order;
            order->type_next = NULL;
            order->type_prev = prev;
        }

        else //middle
        {
            cursor->type_prev->type_next = order;
            order->type_prev = cursor->type_prev;
            cursor->type_prev = order;
            order->type_next = cursor;
        }
    }

    else
    {
        if (1 == product->sell_levels)
            return;
        cursor = product->sell_orders;
        while ((cursor != NULL) && !loc)
        {
            if (cursor->price < order->price)
            {
                prev = cursor;
                cursor = cursor->type_next;
                count++;
            } 

            else if ( (cursor->price == order->price) && 
                (cursor->time < order->time) )
            {
                prev = cursor;
                cursor = cursor->type_next;
                count++;
            }

            else
            {
                loc = true;
            }
        }

        if (1 == count) //should be first
        {
            product->sell_orders->type_prev = order;
            order->type_next = product->sell_orders;
            order->type_prev = NULL;
            product->sell_orders = order;
        }

        else if (!loc) // should be last
        {
            prev->type_next = order;
            order->type_next = NULL;
            order->type_prev = prev;
        }

        else //middle
        {
            cursor->type_prev->type_next = order;
            order->type_prev = cursor->type_prev;
            cursor->type_prev = order;
            order->type_next = cursor;
        }
    }
}
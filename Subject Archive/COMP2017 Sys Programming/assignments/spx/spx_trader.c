#include "spx_trader.h"

void sig_handler(int signo, siginfo_t* sinfo, void* context)
{
   //printf("[%d %d]", fd_read, self_write);
    printf(DEBUG, "sig recieved");
    char buf[BUF_SZ] = {0};
    read(fd_read, buf, BUF_SZ);
    int read_size = strlen(buf);
    //printf(DEBUG_INT, buf, read_size);

    write(self_write, &read_size, INT_SZ);
    write(self_write, buf, read_size);
    to_read = true;

    // char expected[BUF_SZ];
    // sprintf(expected, "ACCEPTED %d;", num_orders);

    // if (0 == strncasecmp(buf, "ACCEPTED", strlen("ACCEPTED"))) 
    // {
    //     //printf(DEBUG, "CONFIRMED");
    //     confirmed = true;
    // } 
    // else
    // {
    //     // printf("s");
    //     // printf(DEBUG, buf);
    //     write(self_write, &read_size, INT_SZ);
    //     write(self_write, buf, read_size);
    //     to_read = true;
    // }
}

// void sig_handler(int signo, siginfo_t* sinfo, void* context)
// {
//     unread++; 
// }

int main(int argc, char ** argv) {
    if (argc < 2) {
        printf("Not enough arguments\n");
        return 1;
    }


    // register signal handler
    struct sigaction sig;
    memset(&sig, 0, sizeof(struct sigaction));
    sig.sa_sigaction = sig_handler; //SETS Handler
    sig.sa_flags = SA_SIGINFO;
    
    if(sigaction(SIGUSR1, &sig, NULL) == -1) 
    {
        perror("sigaction failed");
        return 1;
    }

    // connect to named pipes
    char write_fifo[BUF_SZ];
    sprintf(write_fifo, FIFO_TRADER, atoi(argv[1]));
    char read_fifo[BUF_SZ];
    sprintf(read_fifo, FIFO_EXCHANGE, atoi(argv[1]));

    fd_read = open(read_fifo, O_RDONLY);
    if (fd_read < 0)
    {
        perror("AT unable to open read pipe");
        return 1;
    }

    int fd_write = open(write_fifo, O_WRONLY);
    if (fd_write < 0)
    {
        perror("AT unable to open write pipe");
        return 1;
    }

    fcntl(fd_write, F_SETFL, O_NONBLOCK);

    int self_pipes[2];
    if (-1 == pipe(self_pipes))
        perror("AT Error making pipes");

    self_write = self_pipes[1];
    fcntl(self_write, F_SETFL, O_NONBLOCK);
    int self_read = self_pipes[0];

    int ex_read = open(write_fifo, O_RDONLY | O_NONBLOCK);

    autotrade(self_read, fd_write, ex_read);

    close(self_write);
    close(self_read);
    close(fd_read);
    close(fd_write);
    return 0;
}

void autotrade(int self_read, int fd_write, int ex_read)
{
    pid_t epid = getppid(); 
    bool cont = true;
    char buf[BUF_SZ];
    //int to_read = false;
    int read_size;
    num_orders = -1;

    char order[BUF_SZ];
    char market[MARKET_LEN];
    char type[TYPE_SZ];
    char product[PROD_LEN];
    int qty;
    int price;
    
    struct pollfd fds[1];
    fds[0].fd = self_read;
    fds[0].events = 0;
    fds[0].events |= POLLIN;

    struct pollfd efds[1];
    fds[0].fd = ex_read;
    fds[0].events = 0;
    fds[0].events |= POLLIN;

    struct timespec waittime;
    waittime.tv_sec = WAIT_SEC;
    waittime.tv_nsec = WAIT_NANO;

    //printf("%d %d %d\n", self_read, fd_write, fd_read);

    while(cont)
    {
        //check if there is something to read
        poll(fds, 1, 0);
        if (!(fds[0].revents & POLLIN))
            to_read = false;

        //if not wait until there is something to read
        while (!to_read)
        {
            pause();
            poll(fds, 1, 0);
            if ((fds[0].revents & POLLIN))
                to_read = true;
        }

        //read from self pipe
        memset(buf, 0, BUF_SZ);
        memset(order, 0, BUF_SZ);

        read(self_read, &read_size, INT_SZ);
        //printf("READING %d BYTES\n", read_size);
        read(self_read, buf, read_size);
        strncpy(order, buf, read_size);

        printf(DEBUG, buf);

        //printf(DEBUG, order);
        int assigned = sscanf(order, 
            "%s %s %s %d %d;", 
            market, 
            type, 
            product, 
            &qty, 
            &price);

        if (assigned == EXP_ASSN)
        {
            // printf(DEBUG, market);
            // printf(DEBUG, type);
            // printf(DEBUG, product);
            // printf(DEBUG_INT, "qty", qty);
            // printf(DEBUG_INT, "price", price);
            if ( 
                (0 == strncasecmp(type, "SELL", strlen("SELL") + 1)) 
                && (0 != qty)
                )
            {

                if (1000 <= qty)
                    cont = false;
                else
                {

                    num_orders++;

                    int len = sprintf(order, 
                        "BUY %d %s %d %d;", 
                        num_orders, 
                        product,
                        qty,
                        price);

                    write(fd_write, order, len);

                    confirmed = false;
                    while(!confirmed)
                    {
                        printf(DEBUG, "SIGNALING");
                        kill(epid, SIGUSR1);
                        nanosleep(&waittime, NULL);
                        poll(efds, 1, 0);

                        if (!(efds[0].revents & POLLIN))
                            confirmed = true;
                    }
                }
                
            }
        }
    }
}
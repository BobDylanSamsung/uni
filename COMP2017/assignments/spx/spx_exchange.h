#ifndef SPX_EXCHANGE_H
#define SPX_EXCHANGE_H

#include "spx_common.h"

#define LOG_PREFIX "[SPX]"

typedef struct sig_data sigdata_t;

struct sig_data {
	pid_t source_pid;
	int signo;
	sigdata_t* next;
};



/*
 * get_products
 * parses the products file and creates orderbook
 *
 * char* filename:: path to products file
 *
 * returns poitner to orderbook struct containing products
 */
orderbook_t* get_products(char* filename);

/*
 * check_files
 * checks to see if files passed are valid
 *
 * int argc:: number of commandline arguments
 * char** argv:: commandline args
 *
 * returns true if valid otherwise false
 */
bool check_files(int argc, char** argv);

/*
 * init_traders
 * opens fifos and launches traders
 *
 * int num_traders:: number of traders to open
 * char ** argv:: command line arguments
 * orderbook_t* ob:: orderbook containing products
 *
 * returns pointer to malloced array of traders
 */
trader_t* init_traders(int num_traders, char** argv, orderbook_t* ob);

/*
 * run_market
 * mainloop for market continues until all traders disconnect
 *
 * orderbook_t* ob:: orderbook
 * trader_t* traders:: pointer to array of traders
 * int num traders:: number of traders
 * 
 * returns nothing
 */
void run_market(orderbook_t* ob, trader_t* traders, int num_traders);

/*
 * make_order
 * calls other functions based on the order parsed
 *
 * char* order_str:: order to be parsed
 * orderboo_t* ob:: orderbook
 * trader_t* traders:: array of traders
 * int num_traders:: number of traders in array
 * int sender:: trdaer id of the sender
 * int count:: number of orders parsed
 *
 *returns true if order was valid otherwise false
 */
bool make_order(char* order_str, orderbook_t* ob, trader_t* traders, int num_traders, int sender, int counter);

/*
 * make_buy
 * creates a buy order
 *
 * orderbook_t* ob:: orderbook
 * char* str:: order string
 * int sender:: trader id of the sender
 * trader_t* traders:: array of traders
 * 
 * returns new order
 */
order_t* make_buy(orderbook_t* ob, char* str, int sender, trader_t* traders);


/*
 * make_sell
 * creates a sell order
 *
 * orderbook_t* ob:: orderbook
 * char* str:: order string
 * int sender:: trader id of the sender
 * trader_t* traders:: array of traders
 * 
 * returns new order
 */
order_t* make_sell(orderbook_t* ob, char* str, int sender, trader_t* traders);

/*
 * print_orderbook
 * displays the orderbook in the required format
 *
 * orderbook_t* orderbook:: orderbook
 *
 * returns nothing
 */
void print_orderbook(orderbook_t* ob);

/*
 * print_positions
 * displays the balances of traders
 *
 * trader_t* traders:: array of traders
 * int num_traders:: number of traders
 * int num_products:: number of products being traded
 *
 * returns nothing
 */
void print_positions(trader_t* traders, int num_traders, int num_products);


/*
 * is_num
 * parses string str and returns true if it is a number otherwise false
 */
bool is_num(char* str);

/*
 * find_product
 * gets the index of the product in the orderbook
 *
 * orderbook_t* ob:: orderbook
 * char* str:: name of the product
 *
 * returns index of product in array in orderbook
 */
int find_product(orderbook_t* ob, char* str);


/*
 * clear_orderbook
 * clears the orderbook and frees alocated memory
 *
 * orderbook_t* ob:: orderbook
 *
 * returns nothing
 */
void clear_orderbook(orderbook_t* ob);

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
void notify(trader_t* traders, int num_traders, char* msg, int tid, char* new_msg);


/*
 *match_orders
 *attempts to match orders in the orderbook and notifys traders if a match is found
 *
 *orderbook_t* ob:: orderbook containing orders
 *traders:: traders participating in the exchange
 *int num_traders: total number of traders in the exchange
 *
 *returns nothing
 */
void match_orders(orderbook_t* ob, trader_t* traders, int num_traders);


/*
 *round
 *rounds float to nearest int
 *
 *float x:: float to round
 *
 *returns rounded value
 */
long long round_float(double x);


/*
 *free_order
 *links adjacent orders in the linked list accordingly and frees the order
 *
 *product_t* product:: product containing the order
 *order_t* order:: order to free
 *
 *returns nothing
 */
void free_order(product_t* product, order_t* order);


/*
 * amend_order
 * changes the quantity and price of an order
 *
 * orderbook_t* ob:: orderbook
 * char* str:: string of amend order
 * int sender:: id of the sender
 * int counter:: number of orders that have been parsed
 *
 * returns the order if valid otherwise NULL
 */
order_t* amend_order(orderbook_t* ob, char* str, int sender, int counter);


/*
 * cancel_order
 * cancels the order and sets price and qty to 0
 * 
 * orderbook_t* ob:: orderbook
 * char* str:: cancel order
 * int sender:: trader id of the sender
 *
 * returns the cancelled order or NULL if invalid
 */
order_t* cancel_order(orderbook_t* ob, char* str, int sender);


/*
 * strcount
 * counts the number of a particular character in a string 
 *
 * char* str:: string
 * char delim:: character to count occurances
 *
 * returns number of occurances
 */
int strcount(char* str, char delim);

/*
 * move_order
 * moves order to new index in linked list after amend
 *
 * product_t* product:: product containing order
 * order_t* order:; order to move
 *
 *returns nothing
 */
void move_order(product_t* product, order_t* order);

#endif

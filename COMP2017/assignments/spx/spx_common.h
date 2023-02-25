#ifndef SPX_COMMON_H
#define SPX_COMMON_H


#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif

#define _POSIX_C_SOURCE 200809L

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>

#define FIFO_EXCHANGE "/tmp/spx_exchange_%d"
#define FIFO_TRADER "/tmp/spx_trader_%d"
#define FEE_PERCENTAGE 0.01
#define BUF_SZ 256
#define PROD_LEN 17 //16 chars + null byte
#define ID_SZ 8 //2097152 max number of args 7 digits + null byte
#define TYPE_SZ 7
#define DEBUG "-----------------------%s\n"
#define DEBUG_INT "-----------------------%s: %d\n"
#define NUM_CURSORS 2


typedef enum type type_t;
typedef enum status status_t;
typedef struct trader trader_t;
typedef struct orderbook orderbook_t;
typedef struct product product_t;
typedef struct order order_t; 
typedef struct stock stock_t;


enum type {
	BUY = 0,
	SELL = 1,
	AMEND = 2,
	CANCEL = 3
};

enum status {
	INIT = 0,
	OPEN = 1,
	CLOSED = 2
};

struct trader {
	pid_t pid;
	int trader_id;
	char fifo_etot[BUF_SZ];
	char fifo_ttoe[BUF_SZ];
	int fd_write;
	int fd_read;
	status_t status;
	stock_t* inventory;
	int num_orders;
};

struct orderbook {
	int num_products;
	product_t* products;
	long long fees;
};

struct product {
	char name[PROD_LEN];
	int buy_levels;
	int sell_levels;
	order_t* orders;
	order_t* sell_orders;
	order_t* buy_orders;
};

struct order {
	char product[PROD_LEN];
	type_t type;
	bool cancelled;
	int id;
	int qty;
	int price;
	order_t* next;
	order_t* prev;
	order_t* type_next;
	order_t* type_prev;
	int sender;
	int time;
};

struct stock {
	char name[PROD_LEN];
	int num;
	long long value;
};

#endif

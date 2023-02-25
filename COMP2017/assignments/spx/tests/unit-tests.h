#ifndef UNITTEST
#define UNITTEST

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>

#include "cmocka.h"
#include "../spx_common.h"
#include "../spx_exchange.h"

typedef enum product_index {
	BEETLES = 0,
	QUEEN = 1,
	NWA = 2,
	ELVIS = 3
} pindex_t;

typedef struct expected_order_out{
    int trader; // trader id
    int trader_orders; // orders trader has placed
    int order_id;
    type_t type; // type of the order
    pindex_t product_index; // index of product in orderbook
    int qty;
    int price;
    int buy_levels; // number of buy levels for product
    int sell_levels; // number of sell levels for product
    int order_index; // index in buy / sell orders for the product
} expected_order_out_t;

typedef struct order_input{
    type_t type;
    int sender;
    char* request;
} order_input_t;

stock_t empty_stock = {
	"",
	0,
	0
};

trader_t test_traders[] = { // 3 traders will unneeded values set to null or -1
	{875402, 0, "", "", -1, -1, OPEN, &empty_stock, 0},
	{875403, 1, "", "", -1, -1, OPEN, &empty_stock, 0},
	{875404, 2, "", "", -1, -1, OPEN, &empty_stock, 0}
};

char product_list[4][PROD_LEN] = { //products from lib/products.txt
	"Beetles",
	"Queen",
	"NWA",
	"Elvis"
};

static void test_get_one_product();

static void test_100_products();

static void test_buy();

static void test_sell();

static void test_buy_and_sells();

static void test_invalid_buy_sell();

static void test_amend_cancel();

#endif
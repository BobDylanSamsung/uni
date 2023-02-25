#include "unit-tests.h"

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_get_one_product),
        cmocka_unit_test(test_100_products),
        cmocka_unit_test(test_buy),
        cmocka_unit_test(test_sell),
        cmocka_unit_test(test_buy_and_sells),
        cmocka_unit_test(test_invalid_buy_sell),
        cmocka_unit_test(test_amend_cancel)

    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

static void test_get_one_product()
{
    char* path = "tests/lib/one_product.txt";
    orderbook_t* ob = get_products(path);

    assert_true(ob != NULL);
    assert_int_equal(ob->num_products, 1);

    product_t product = ob->products[0];

    assert_string_equal(product.name, "Router");
    assert_true(product.orders == NULL);
    assert_true(product.buy_orders == NULL);
    assert_true(product.sell_orders == NULL);
    assert_int_equal(product.buy_levels, 0);
    assert_int_equal(product.sell_levels, 0);
    clear_orderbook(ob);
    free(ob->products);
    free(ob);
}

static void test_100_products()
{
    char names[100][PROD_LEN] = {
        "flow", 
        "youth", 
        "regard", 
        "steward", 
        "current", 
        "evaluate", 
        "situation", 
        "inch", 
        "material", 
        "quotation", 
        "node", 
        "pit", 
        "smash", 
        "discourage", 
        "advice", 
        "guideline", 
        "chord", 
        "superintendent", 
        "diamond", 
        "destruction", 
        "drag", 
        "beam", 
        "battlefield", 
        "inquiry", 
        "stadium", 
        "economic", 
        "withdraw", 
        "rape", 
        "survival", 
        "bend", 
        "veil", 
        "leak", 
        "bless", 
        "combine", 
        "satisfaction", 
        "close", 
        "prosecute", 
        "piece", 
        "fountain", 
        "delete", 
        "witness", 
        "portrait", 
        "abnormal", 
        "thrust", 
        "flatware", 
        "recover", 
        "cook", 
        "on", 
        "area", 
        "password", 
        "muggy", 
        "tax", 
        "creep", 
        "mechanism", 
        "wealth", 
        "parameter", 
        "cultivate", 
        "harm", 
        "soak", 
        "possibility", 
        "feminine", 
        "understanding", 
        "excavation", 
        "difference", 
        "shelter", 
        "plug", 
        "dismiss", 
        "snake", 
        "brilliance", 
        "tie", 
        "recording", 
        "member", 
        "summary", 
        "we", 
        "node", 
        "reptile", 
        "regard", 
        "bay", 
        "exotic", 
        "manufacturer", 
        "jam", 
        "taste", 
        "spirit", 
        "factory", 
        "reality", 
        "sulphur", 
        "flush", 
        "suspicion", 
        "person", 
        "education", 
        "window", 
        "weak", 
        "charge", 
        "Europe", 
        "cooperate", 
        "treat", 
        "establish", 
        "ally", 
        "cancer", 
        "symptom"
    };

    char* path = "tests/lib/100_products.txt";

    orderbook_t* ob = get_products(path);

    assert_int_equal(ob->num_products, 100);

    for (int i = 0; i < 100; i++)
    {
        product_t product = ob->products[i];
        assert_string_equal(names[i], product.name);
        assert_true(product.orders == NULL);
        assert_true(product.buy_orders == NULL);
        assert_true(product.sell_orders == NULL);
        assert_int_equal(product.buy_levels, 0);
        assert_int_equal(product.sell_levels, 0);
    }
    clear_orderbook(ob);
    free(ob->products);
    free(ob);
}


static void test_buy()
{
    //setup
    trader_t* const traders = test_malloc(sizeof(test_traders));
    memcpy(traders, test_traders, sizeof(test_traders));
    
    //run test

    orderbook_t* ob = get_products("tests/lib/products.txt");

    char* str = "0 Beetles 10 100";

    order_t* order = make_buy(ob, str, 0, traders);

    assert_true(order != NULL);
    assert_int_equal(1, traders[0].num_orders);

    assert_string_equal(order->product, "Beetles");
    assert_int_equal(order->id, 0);
    assert_int_equal(order->qty, 10);
    assert_int_equal(order->price, 100);
    assert_int_equal(order->sender, 0);

    product_t product = ob->products[0];

    assert_int_equal(product.buy_levels, 1);
    assert_int_equal(product.sell_levels, 0);
    assert_true(product.sell_orders == NULL);
    assert_true(product.buy_orders != NULL);
    assert_true(product.buy_orders == order);

    clear_orderbook(ob);
    free(ob->products);
    free(ob);

    test_free(traders);
}

static void test_sell()
{
    //setup
    trader_t* const traders = test_malloc(sizeof(test_traders));
    memcpy(traders, test_traders, sizeof(test_traders));
    
    //run test

    orderbook_t* ob = get_products("tests/lib/products.txt");

    char* str = "0 NWA 50 55";

    order_t* order = make_sell(ob, str, 1, traders);

    assert_true(order != NULL);
    assert_int_equal(1, traders[1].num_orders);

    assert_string_equal(order->product, "NWA");
    assert_int_equal(order->id, 0);
    assert_int_equal(order->qty, 50);
    assert_int_equal(order->price, 55);
    assert_int_equal(order->sender, 1);

    product_t product = ob->products[2];

    assert_int_equal(product.buy_levels, 0);
    assert_int_equal(product.sell_levels, 1);
    assert_true(product.sell_orders != NULL);
    assert_true(product.buy_orders == NULL);
    assert_true(product.sell_orders == order);

    clear_orderbook(ob);
    free(ob->products);
    free(ob);

    test_free(traders);
}

static void test_buy_and_sells()
{
    //setup
    trader_t* const traders = test_malloc(sizeof(test_traders));
    memcpy(traders, test_traders, sizeof(test_traders));


    int num_orders = 8;

    order_input_t inputs[] = {
        {BUY, 0, "0 Beetles 10 100"},
        {BUY, 1, "0 Queen 20 30"},
        {SELL, 2, "0 NWA 100 1000"},
        {SELL, 2, "1 Beetles 150 25"},
        {SELL, 1, "1 NWA 50 1000"},
        {BUY, 2, "2 NWA 90 500"},
        {BUY, 0, "1 Elvis 5 1"},
        {BUY, 0, "2 Beetles 5000 500"}
    };

    expected_order_out_t expected_out[] = {
        {0, 1, 0, BUY, BEETLES, 10, 100, 1, 0, 0},
        {1, 1, 0, BUY, QUEEN, 20, 30, 1, 0, 0},
        {2, 1, 0, SELL, NWA, 100, 1000, 0, 1, 0},
        {2, 2, 1, SELL, BEETLES, 150, 25, 1, 1, 0},
        {1, 2, 1, SELL, NWA, 50, 1000, 0, 2, 1},
        {2, 3, 2, BUY, NWA, 90, 500, 1, 2, 0},
        {0, 2, 1, BUY, ELVIS, 5, 1, 1, 0, 0},
        {0, 3, 2, BUY, BEETLES, 5000, 500, 2, 1, 0}
    };

    orderbook_t* ob = get_products("tests/lib/products.txt");

    
    //run tests
    for (int i = 0; i < num_orders; i++)
    {
        //printf("Running test %d\n", i);
        order_t* order;
        if (inputs[i].type == BUY)
            order = make_buy(ob, inputs[i].request, inputs[i].sender, traders);
        else
            order = make_sell(ob, inputs[i].request, inputs[i].sender, traders);

        assert_true(order != NULL); // check valid

        
        trader_t trader = traders[inputs[i].sender];
        expected_order_out_t expected = expected_out[i];


        assert_int_equal(trader.num_orders, expected.trader_orders); // check number of orders for trader
        assert_string_equal(order->product, product_list[expected.product_index]); // product name
        assert_int_equal(order->id, expected.order_id); // order id
        assert_int_equal(order->qty, expected.qty);
        assert_int_equal(order->price, expected.price);
        assert_int_equal(order->sender, expected.trader); // trader id matched

        product_t product = ob->products[expected.product_index];

        assert_int_equal(product.buy_levels, expected.buy_levels);
        assert_int_equal(product.sell_levels, expected.sell_levels);
        
        //check position in orderbook
        order_t* cursor;
        if (inputs[i].type == BUY)
            cursor = product.buy_orders;
        else
            cursor = product.sell_orders;

        for(int j = 0; j < expected.order_index; j++)
            cursor = cursor->type_next;

        assert_true(cursor == order);
    }
    

    clear_orderbook(ob);
    free(ob->products);
    free(ob);

    test_free(traders);
}

static void test_invalid_buy_sell()
{
    trader_t* const traders = test_malloc(sizeof(test_traders));
    memcpy(traders, test_traders, sizeof(test_traders));
    orderbook_t* ob = get_products("tests/lib/products.txt");

    int num_orders = 18;

    order_input_t inputs[] = {
        {BUY, 0, "0 Beeetles 10 100"},
        {BUY, 1, "1 Beetles 10 100"},
        {BUY, 2, "0 Beetles 0 100"},
        {BUY, 1, "0 Beetles 10000000 100"},
        {BUY, 1, "0 Beetles 10 0"},
        {BUY, 2, "0 Queen 20 9999999"},
        {BUY, 0, "Queen 20 9999999"},
        {BUY, 1, "0 Queen 20"},
        {SELL, 0, "0 Beeetles 10 100"},
        {SELL, 1, "1 Beetles 10 100"},
        {SELL, 2, "0 Beetles 0 100"},
        {SELL, 1, "0 Beetles 10000000 100"},
        {SELL, 1, "0 Beetles 10 0"},
        {SELL, 2, "0 Queen 20 9999999"},
        {SELL, 0, "Queen 20 9999999"},
        {SELL, 1, "0 Queen 20"},
        {BUY, 1, ""},
        {SELL, 1, ""}
    };

    for (int i = 0; i < num_orders; i++)
    {
        //printf("Running test %d\n", i);
        order_t* order;
        if (inputs[i].type == BUY)
            order = make_buy(ob, inputs[i].request, inputs[i].sender, traders);
        else
            order = make_sell(ob, inputs[i].request, inputs[i].sender, traders);

        assert_true(order == NULL); // check invalid
    }

    clear_orderbook(ob);
    free(ob->products);
    free(ob);

    test_free(traders);
}

static void test_amend_cancel()
{
    trader_t* const traders = test_malloc(sizeof(test_traders));
    memcpy(traders, test_traders, sizeof(test_traders));


    int num_orders = 13;

    order_input_t inputs[] = {
        {BUY, 0, "0 Beetles 10 100"},
        {BUY, 1, "0 Queen 20 30"},
        {SELL, 2, "0 NWA 100 1000"},
        {SELL, 2, "1 Beetles 150 25"},
        {SELL, 1, "1 NWA 50 1000"},
        {BUY, 2, "2 NWA 90 500"},
        {BUY, 0, "1 Elvis 5 1"},
        {BUY, 0, "2 Beetles 5000 500"},
        {AMEND, 0, "0 123 456"},
        {AMEND, 2, "1 69 420"},
        {CANCEL, 1, "1"},
        {CANCEL, 0, "1"},
        {AMEND, 2, "1 50 500"}
    };

    expected_order_out_t expected_out[] = {
        {0, 1, 0, BUY, BEETLES, 10, 100, 1, 0, 0},
        {1, 1, 0, BUY, QUEEN, 20, 30, 1, 0, 0},
        {2, 1, 0, SELL, NWA, 100, 1000, 0, 1, 0},
        {2, 2, 1, SELL, BEETLES, 150, 25, 1, 1, 0},
        {1, 2, 1, SELL, NWA, 50, 1000, 0, 2, 1},
        {2, 3, 2, BUY, NWA, 90, 500, 1, 2, 0},
        {0, 2, 1, BUY, ELVIS, 5, 1, 1, 0, 0},
        {0, 3, 2, BUY, BEETLES, 5000, 500, 2, 1, 0},
        {0, 3, 0, BUY, BEETLES, 123, 456, 2, 1, 1},
        {2, 3, 1, SELL, BEETLES, 69, 420, 2, 1, 0},
        {1, 2, 1, SELL, NWA, 0, 0, 1, 2, 1},
        {0, 3, 1, BUY, ELVIS, 0, 0, 1, 0, 0},
        {2, 3, 1, SELL, BEETLES, 50, 500, 2, 1, 0}
    };

    orderbook_t* ob = get_products("tests/lib/products.txt");

    
    //run tests
    for (int i = 0; i < num_orders; i++)
    {
        //printf("Running test %d: %d %s\n", i, inputs[i].sender, inputs[i].request);
        order_t* order;
        if (inputs[i].type == BUY)
            order = make_buy(ob, inputs[i].request, inputs[i].sender, traders);
        else if (inputs[i].type == SELL)
            order = make_sell(ob, inputs[i].request, inputs[i].sender, traders);
        else if (inputs[i].type == AMEND)
            order = amend_order(ob, inputs[i].request, inputs[i].sender, i);
        else
            order = cancel_order(ob, inputs[i].request, inputs[i].sender);

        assert_true(order != NULL); // check valid

        
        trader_t trader = traders[inputs[i].sender];
        expected_order_out_t expected = expected_out[i];


        assert_int_equal(trader.num_orders, expected.trader_orders); // check number of orders for trader
        assert_string_equal(order->product, product_list[expected.product_index]); // product name
        assert_int_equal(order->id, expected.order_id); // order id
        assert_int_equal(order->qty, expected.qty);
        assert_int_equal(order->price, expected.price);
        assert_int_equal(order->sender, expected.trader); // trader id matched

        product_t product = ob->products[expected.product_index];

        assert_int_equal(product.buy_levels, expected.buy_levels);
        assert_int_equal(product.sell_levels, expected.sell_levels);
        
        //check position in orderbook
        order_t* cursor;
        if (order->type == BUY)
            cursor = product.buy_orders;
        else
            cursor = product.sell_orders;

        //printf("cursor: %p\n", cursor);

        for(int j = 0; j < expected.order_index; j++)
        {
            cursor = cursor->type_next;
            //printf("cursor: %p\n", cursor);

        }

        //printf("%p %p\n", order, cursor);
        assert_true(cursor == order);

        if (inputs[i].type == CANCEL)
        {
            int prod_index = find_product(ob, order->product);
            product_t* product = &ob->products[prod_index];
            
            if (BUY == order->type)
                product->buy_levels--;
            else
                product->sell_levels--;

            free_order(product, order);
        }
    }
    

    clear_orderbook(ob);
    free(ob->products);
    free(ob);

    test_free(traders);
}


#ifndef SPX_TRADER_H
#define SPX_TRADER_H

#include "spx_common.h"
#include <time.h>

#define EXP_ASSN 5
#define MARKET_LEN 10
#define SELF_FIFO "/tmp/spx_AT_SELF"
#define WAIT_SEC 0
#define WAIT_NANO 100000000
#define INT_SZ 4

void autotrade(int self_read, int fd_write, int ex_read);
void autotrade_old(int fd_read, int fd_write);
void await_confirmation(pid_t epid, int num_orders);


//int unread = 0;
int self_write;
int fd_read;
bool to_read;
bool confirmed;
int num_orders;


#endif

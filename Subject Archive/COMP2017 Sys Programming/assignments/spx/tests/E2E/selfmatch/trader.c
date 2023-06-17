#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>

#define FIFO_EXCHANGE "/tmp/spx_exchange_%d"
#define FIFO_TRADER "/tmp/spx_trader_%d"
#define BUF_SZ 256
#define PROD_LEN 17 //16 chars + null byte
#define ID_SZ 8 //2097152 max number of args 7 digits + null byte
#define TYPE_SZ 7
#define DEBUG "-----------------------%s\n"
#define DEBUG_INT "-----------------------%s: %d\n"

void sig_handler(int signo, siginfo_t* sinfo, void* context)
{
    return;
}



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


    int fd_read = open(read_fifo, O_RDONLY);
    if (fd_read < 0)
    {
        perror("child unable to open read pipe");
        return 1;
    }

    int fd_write = open(write_fifo, O_WRONLY);
    if (fd_write < 0)
    {
        perror("child unable to open write pipe");
        return 1;
    }

    fcntl(fd_write, F_SETFL, O_NONBLOCK);

    pid_t ppid = getppid();
    char buf[BUF_SZ];    
    memset(buf, 0, BUF_SZ);


    int num_orders = 8;
    int orders_placed = 0;

    char* orders[BUF_SZ] = {
        "BUY 0 BEETLES 10 2;",
        "SELL 1 beetles 10 2;",
        "SELL 2 elvis 13 12345;",
        "BUY 3 elvis 13 12345;",
        "SELL 4 beetles 350 450;",
        "BUY 5 beetles 1010 10000;",
        "BUY 6 NWA 1190 90000;",
        "SELL 7 NWA 240 90000;"
    };

    char order[BUF_SZ];

    struct pollfd fds[1];
    fds[0].fd = fd_read;
    fds[0].events = 0;
    fds[0].events |= POLLIN;
    int timeout = -1;

    //wait for market open
    poll(fds, 1, timeout);
    read(fd_read, buf, BUF_SZ);
    //printf(DEBUG, buf);
    memset(buf, 0, BUF_SZ);

    bool waiting_confirmation = false;
    
    while(orders_placed < num_orders || waiting_confirmation)
    {
        if(waiting_confirmation)
        {
            poll(fds, 1, timeout);
            read(fd_read, buf, BUF_SZ);
            //printf(DEBUG, buf);
            memset(buf, 0, BUF_SZ);
            waiting_confirmation = false;
        }

        else
        {
            strncpy(order, orders[orders_placed], BUF_SZ);
            write(fd_write, order, BUF_SZ);
            kill(ppid, SIGUSR1);
            waiting_confirmation = true;
            orders_placed++;
        }
    }

    close(fd_write);
    close(fd_read);

    return 0;    

}
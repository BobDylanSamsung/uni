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

    pid_t exchange_pid = getppid();

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

    char buf[BUF_SZ];


    // wait for exchange update (MARKET message)
    pause();
    read(fd_read, buf, BUF_SZ);

    //send order
    char* order = "BUY 0 GPU 30 500;";
    strncpy(buf, order, strlen(order));
    write(fd_write, buf, strlen(order));
    kill(exchange_pid, SIGUSR1);
    // wait for exchange confirmation (ACCEPTED message)
    pause();
    read(fd_read, buf, BUF_SZ);

    //send order
    order = "BUY 1 GPU 35 500;";
    strncpy(buf, order, strlen(order));
    write(fd_write, buf, strlen(order));
    kill(exchange_pid, SIGUSR1);
    // wait for exchange confirmation (ACCEPTED message)
    pause();
    read(fd_read, buf, BUF_SZ);

    //send order
    order = "BUY 2 ROUTER 15 10;";
    strncpy(buf, order, strlen(order));
    write(fd_write, buf, strlen(order));
    kill(exchange_pid, SIGUSR1);
    // wait for exchange confirmation (ACCEPTED message)
    pause();
    read(fd_read, buf, BUF_SZ);

    //send order
    order = "BUY 3 GPU 40 499;";
    strncpy(buf, order, strlen(order));
    write(fd_write, buf, strlen(order));
    kill(exchange_pid, SIGUSR1);
    // wait for exchange confirmation (ACCEPTED message)
    pause();
    read(fd_read, buf, BUF_SZ);

    //send order
    order = "BUY 4 GPU 10 501;";
    strncpy(buf, order, strlen(order));
    write(fd_write, buf, strlen(order));
    kill(exchange_pid, SIGUSR1);
    // wait for exchange confirmation (ACCEPTED message)
    pause();
    read(fd_read, buf, BUF_SZ);

    //send order
    order = "BUY 5 ROUTER 999999 999999;";
    strncpy(buf, order, strlen(order));
    write(fd_write, buf, strlen(order));
    kill(exchange_pid, SIGUSR1);
    // wait for exchange confirmation (ACCEPTED message)
    pause();
    read(fd_read, buf, BUF_SZ);

    close(fd_write);
    close(fd_read);

    return 0;    

}
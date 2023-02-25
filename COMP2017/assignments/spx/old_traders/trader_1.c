#include "spx_trader.h"

void sig_handler(int signo, siginfo_t* sinfo, void* context)
{
    //printf("trader 0 received signal\n");    
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


    int fd_write = open(write_fifo, O_WRONLY);
    if (fd_write < 0)
    {
        perror("child unable to open write pipe");
        return 1;
    }

    int fd_read = open(read_fifo, O_RDONLY);
    if (fd_read < 0)
    {
        perror("child unable to open read pipe");
        return 1;
    }

    char buf[BUF_SZ];

    //receive exchange pid
    pid_t exchange_pid = getppid(); 


    // wait for exchange update (MARKET message)
    pause();
    read(fd_read, buf, BUF_SZ);

    //wait for trader 0 orders
    pause();
    pause();
    pause();

    //send order
    char* order;

    order = "BUY 0 ROUTER 10 501;";
    strncpy(buf, order, strlen(order));
    write(fd_write, buf, strlen(order));
    kill(exchange_pid, SIGUSR1);
    // wait for exchange confirmation (ACCEPTED message)
    pause();
    read(fd_read, buf, BUF_SZ);

    pause();
    sleep(3);


    close(fd_write);
    close(fd_read);

    // while (count <= 5)
    // {
    //     pause();
    // }
    printf("\t\t\tbye1\n");
    return 0;    
}
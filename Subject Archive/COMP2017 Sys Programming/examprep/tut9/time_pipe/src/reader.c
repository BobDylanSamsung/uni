#include "reader.h"

void sig_handler(int signo, siginfo_t* sinfo, void* context)
{
	write(fd_write, "EAT MY ASS", strlen("EAT MY ASS"));
	kill(ppid, SIGUSR1);
    return;
}


int main(int argc, char ** argv) {
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

    fd_write = open("/tmp/TIMETELLER", O_WRONLY);
    if (fd_write < 0)
    {
        perror("unable to open write pipe");
        return 1;
    }

    fcntl(fd_write, F_SETFL, O_NONBLOCK);

    ppid = getppid();

    while(1)
    {
    	pause();
    }

    close(fd_write);
    return 0;
}
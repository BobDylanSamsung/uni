#include "time.h"

void sig_handler(int signo, siginfo_t* sinfo, void* context)
{
	char buf[256] = {0};
	read(fd_read, buf, 256);
	printf("%s\n", buf);
}

int main() {

	//set up signals
    struct sigaction sig;
    memset(&sig, 0, sizeof(struct sigaction));
    sig.sa_sigaction = sig_handler; //SETS Handler
    sig.sa_flags = SA_SIGINFO | SA_RESTART;
    
    if(sigaction(SIGUSR1, &sig, NULL) == -1) 
    {
        perror("sigaction failed");
        return 1;
    }


    //set up pipes
    if (0>mkfifo("/tmp/TIMETELLER", S_IRWXU | S_IRWXG))
    {
    	perror("unable to open fifo");
    }

    pid_t pid = fork();

    if (0 == pid)
    {
		if (execl("reader", "reader", NULL) == -1)
        {
            perror("exec failed");
            return 1;
        }
    }

	fd_read = open("/tmp/TIMETELLER", O_RDONLY);

	while(1)
	{
		pause();
	}

	return 0;
}
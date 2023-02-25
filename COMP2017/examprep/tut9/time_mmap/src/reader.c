#include "reader.h"

void sig_handler(int signo, siginfo_t* sinfo, void* context)
{
	while (mem[offset] != '\0')
    {
        printf("%c\n", mem[offset]);
        offset++;
    }
    printf("\n");
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

    int fd = shm_open("/tmp/time_mmap")
    ftruncate(fd, 1000);
    mem = mmap(NULL, 1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    while(1)
    {
    	pause();
    }

    munmap(mem, 1000);
    return 0;
}
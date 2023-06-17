#include "time.h"

int main() {

    pid_t pid = fork();

    if (0 == pid)
    {
		if (execl("reader", "reader", NULL) == -1)
        {
            perror("exec failed");
            return 1;
        }
    }

    int fd = shm_open("/tmp/time_mmap", O_RDWR|O_CREAT, S_IRUSR | S_IWUSR);
    ftruncate(fd, 1000);

    char* mem = mmap(NULL, 1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);




    char buf[256] = {0};
    int offset = 0;
	
    while(strcmp(fgets(buf, 32, stdin), "\n") && offset < 1000){
        
        //if last character of input is newline, remove it
        if('\n' == buf[strlen(buf) - 1]){
            buf[strlen(buf) - 1] = '\0';
        }

        for (int i; i < strlen(buf) + 1; i++)
        {
            mem[i + offset] = buf[i];
            offset++;
        }

        kill(pid, SIGUSR1);

	}

	return 0;
}
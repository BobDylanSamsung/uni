#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <poll.h>

#define BUF_SZ 256
#define INT_SZ 4

typedef struct _process {
    pid_t pid;
    int read_pipe;
    int complete;
} process_t;

process_t* processes;
int num_processes;
int more_to_read;

int is_delim(char c, char* delims)
{
    int i = 0;
    while (delims[i] != '\0')
    {
        if (delims[i] ==  c)
            return 1;
        i++;
    }
    return 0;
}


void sig_handler(int signo, siginfo_t* sinfo, void* context)
{
    printf("sig %d caught by %d\n", signo, sinfo->si_pid);

    if (signo == SIGCHLD)
    {
        for (int i = 0; i < num_processes; i++)
        {
            if (processes[i].pid == sinfo->si_pid)
            {
                processes[i].complete = 1;
                more_to_read--;
                return;
            }
        }
    }
    return;
}

void read_files(char* filename, int write_pipe, pid_t ppid, char* delims)
{
    FILE* file = fopen(filename, "r");
    char buf[BUF_SZ] = {0};
    int size = 0;
    char cur = (char)fgetc(file);

    pause();
    while (cur != EOF)
    {
        if(!(size == 0 && is_delim(cur, delims)))
        {
            if (is_delim(cur, delims))
            {
                write(write_pipe, &size, INT_SZ);
                write(write_pipe, buf, size);
                // printf("[%s: %s]\n",filename, buf);
                size = 0;
                memset(buf, 0, BUF_SZ);
                kill(ppid, SIGUSR1);
                pause();
                // printf("reading %s ", filename);
            }
            else if (cur != '\n')
            {
                buf[size] = cur;
                size++;
                if (size == BUF_SZ)
                {
                    write(write_pipe, &size, INT_SZ);
                    write(write_pipe, buf, size);
                    size = 0;
                    memset(buf, 0, BUF_SZ);
                }    
            }    
        }
        
        cur = (char)fgetc(file);
    }

    if (size > 0)
    {
        write(write_pipe, &size, INT_SZ);
        write(write_pipe, buf, size);
        size = 0;
        memset(buf, 0, BUF_SZ);
        kill(ppid, SIGUSR1);
    }
    size = -1;
    write(write_pipe, &size, INT_SZ);
}

int launch_processes(int argc, char** argv, process_t* processes)
{
    for (int i = 0; i < argc - 3; i++)
    {
        char* filename = argv[3 + i];
        int pipe_fds[2];

        if (-1 == pipe(pipe_fds))
        {
            perror("Can't open pipes");
            return -1;
        }

        processes[i].complete = 0;

        pid_t pid = fork();

        if (0 > pid)
        {
            perror("Unable to fork");
            return -1;
        }

        if (0 == pid)
        {
            //child
            int write_pipe = pipe_fds[1];
            close(pipe_fds[0]);
            pid_t ppid = getppid();
            free(processes);
            read_files(filename, write_pipe, ppid, argv[2]);
            return 0;
        }

        close(pipe_fds[1]);
        processes[i].read_pipe = pipe_fds[0];
    }
    return 1;
}






void mainloop(process_t* processes, int num_processes, char** argv)
{
    int current = 0;
    more_to_read = num_processes;
    int read_size = 0;

    while (more_to_read > 0 || current != 0)
    {
        if (current == 0)
            printf("\n");
        // printf("SIGNALLING %s\n", argv[current + 3]);
        kill(processes[current].pid, SIGUSR1);
        pause();

        struct pollfd pfd = {
            .fd = processes[current].read_pipe, 
            .events = POLLIN
        };
        poll(&pfd, 1, 0);

        if (processes[current].complete && !(pfd.revents & POLLIN))
        {
            printf("%s no more tokens\n", argv[3 + current]);
        } 

        else
        {
            char buf[BUF_SZ + 1] = {0};

            poll(&pfd, 1, 0);
            while(pfd.revents & POLLIN)
            {
                read(processes[current].read_pipe, &read_size, INT_SZ);
                if (read_size < 0)
                {
                    processes[current].complete = 1;
                }
                else
                {
                    read(processes[current].read_pipe, buf, read_size);
                    printf("%s\n", buf);
                    memset(buf, 0, BUF_SZ);
                }
                poll(&pfd, 1, 0);
            }
            printf("\n");
            current = (current + 1) % num_processes;
        }
    }
}

int student_main(int argc, char **argv)
{
    struct sigaction sig;
    memset(&sig, 0, sizeof(struct sigaction));
    sig.sa_sigaction = sig_handler; //SETS Handler
    sig.sa_flags = SA_SIGINFO | SA_RESTART;
    
    if(sigaction(SIGUSR1, &sig, NULL) == -1) 
    {
        perror("sigaction failed");
        return 1;
    }
    if(sigaction(SIGCHLD, &sig, NULL) == -1) 
    {
        perror("sigaction failed");
        return 1;
    }


    if (argc < 4)
    {
        printf("Not enough CL args\n");
        return 1;
    }


    processes = malloc(sizeof(process_t) * (argc - 3));
    num_processes = argc - 3;
    int child = launch_processes(argc, argv, processes);

    if (child < 0)
    {
        free(processes);
        return -1;
    }

    if (child == 0)
    {
        return 0;
    }

    mainloop(processes, argc - 3, argv);

    return 0;
}




/*
 * DO NOT MODIFY THIS MAIN FUNCTION
 */
int main(int argc, char **argv) // #157471
{
    return student_main(argc, argv);
}

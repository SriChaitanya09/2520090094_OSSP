#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child Process\n");
        printf("PID : %d\n", getpid());

        exit(0);
    }
    else
    {
        printf("Parent Process\n");
        printf("PID : %d\n", getpid());

        wait(NULL);

        printf("Child collected successfully.\n");
        printf("No Zombie Process.\n");
    }

    return 0;
}

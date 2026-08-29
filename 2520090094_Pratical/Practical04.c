#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0)
    {
        printf("Child 1\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());

        sleep(2);

        printf("Child 1 Finished\n");
        exit(0);
    }

    pid2 = fork();

    if (pid2 == 0)
    {
        printf("Child 2\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());

        sleep(4);

        printf("Child 2 Finished\n");
        exit(0);
    }

    printf("\nParent Process\n");
    printf("Parent PID : %d\n", getpid());

    wait(NULL);
    printf("One child completed using wait().\n");

    waitpid(pid2, NULL, 0);
    printf("Second child completed using waitpid().\n");

    printf("All child processes completed.\n");

    return 0;
}

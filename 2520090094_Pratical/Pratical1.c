#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char command[100];
    pid_t pid;

    printf("Enter a Linux command: ");
    fgets(command, sizeof(command), stdin);

    // Remove the newline character added by fgets()
    command[strcspn(command, "\n")] = '\0';

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("\n--- Child Process ---\n");
        printf("Child PID : %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        printf("Executing command: %s\n\n", command);

        execl("/bin/sh", "sh", "-c", command, NULL);

        // Executes only if execl() fails
        printf("Command execution failed!\n");
    }
    else
    {
        // Parent process
        printf("\n--- Parent Process ---\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);

        wait(NULL);

        printf("\nChild process has finished execution.\n");
    }

    return 0;
}

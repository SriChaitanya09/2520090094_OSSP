#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 100000

int main()
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        // Parent - Producer
        close(pipefd[0]);

        clock_t start = clock();

        for (int i = 0; i < N; i++)
        {
            if (write(pipefd[1], &i, sizeof(i)) == -1)
            {
                perror("write");
                close(pipefd[1]);
                return 1;
            }
        }

        close(pipefd[1]);

        clock_t end = clock();

        double time_taken =
            (double)(end - start) / CLOCKS_PER_SEC;

        printf("Producer: Sent %d items\n", N);
        printf("Time taken: %f seconds\n", time_taken);

        wait(NULL);
    }
    else
    {
        // Child - Consumer
        close(pipefd[1]);

        int value;
        int count = 0;

        while (read(pipefd[0], &value, sizeof(value)) > 0)
        {
            count++;
        }

        close(pipefd[0]);

        printf("Consumer: Received %d items\n", count);
    }

    return 0;
}
     

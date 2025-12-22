#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *argv[2];
    pid_t pid;
    extern char **environ;

    while (1)
    {
    if (isatty(STDIN_FILENO))
{
        printf("cisfun$ ");
        fflush(stdout);
}
        nread = getline(&line, &len, stdin);

        if (nread == -1)
            break;

        if (nread == 1)
            continue;

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            continue;
        }

        if (pid == 0)
        {
            argv[0] = line;
            argv[1] = NULL;

            if (execve(argv[0], argv, environ) == -1)
            {
                printf("./shell: No such file or directory\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
        }
    }

    free(line);
    return 0;
}


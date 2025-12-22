#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *trim_line(char *str)
{
    char *start = str;
    char *end;

    while (*start == ' ' || *start == '\t')
        start++;

    if (*start == '\0')
        return start;

    end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return start;
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *argv[2];
    pid_t pid;
    extern char **environ;
    char *trimmed;

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

        trimmed = trim_line(line);
        if (*trimmed == '\0')
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            continue;
        }

        if (pid == 0)
        {
            argv[0] = trimmed;
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

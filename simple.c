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

int main(int argc, char **argv, char **env)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[2];
    pid_t pid;
    extern char **environ;
    char *trimmed;
    FILE *fp;



        if (argc == 2)
        {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
        perror("./shell");
        return(1);
        }
        }
        else
        {
        fp = stdin;
        }

    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("cisfun$ ");
            fflush(stdout);
        }

        nread = getline(&line, &len, fp);
        
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
            args[0] = trimmed;
            args[1] = NULL;
            if (execve(args[0], args, env) == -1)
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

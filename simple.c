#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
char *trim(char *str);


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

	line = trim(line);

	if (line[0] == '\0')
    	    continue;

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



char *trim(char *str)
{
    char *end;

    while (*str == ' ' || *str == '\t') str++;
    if (*str == 0) return str;

    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t')) end--;
    *(end + 1) = '\0';
    return str;
}

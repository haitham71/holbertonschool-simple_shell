#include "shell_headers.h"

/* This is our simple shell implementation
@badr & @haitham */

/*main function*/

int main(int argc, char **argv, char **env)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
char *args[64];
pid_t pid;
char *token;
int i;
FILE *fp;

if (argc == 2)
{
fp = fopen(argv[1], "r");
if (fp == NULL)
{
perror(argv[0]);
return (1);
}
}
else
fp = stdin;

while (1)
{
if (fp == stdin && isatty(STDIN_FILENO))
{
printf("cisfun$ ");
fflush(stdout);
}

nread = getline(&line, &len, fp);
if (nread == -1)
break;

if (line[nread - 1] == '\n') line[nread - 1] = '\0';

i = 0;
token = strtok(line, " \t");
while (token != NULL && i < 63)
{
args[i++] = token;
token = strtok(NULL, " \t");
}
args[i] = NULL;

if (args[0] == NULL)
continue;

pid = fork();

if (pid == 0)
{
if (execve(args[0], args, env) == -1)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
exit(127);
}
}
else
wait(NULL);
}

free(line);
if (fp != stdin) fclose(fp);
return (0);
}

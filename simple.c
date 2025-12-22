#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - مفسر أوامر بسيط (Simple Shell)
 * يستخدم getline للقراءة و execve للتنفيذ
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
char *argv[] = {NULL, NULL};
pid_t pid;
while (1)
{
printf("cisfun$ ");
fflush(stdout);
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
if (execve(argv[0], argv, NULL) == -1)
{
perror("./shell");
exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}
}
free(line);
return (0);
}
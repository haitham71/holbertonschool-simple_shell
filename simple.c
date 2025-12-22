#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
char *argv[] = {NULL, NULL};
pid_t pid;
char line[1024];

while (1)
{
printf("cisfun$ ");

fgets(line, sizeof(line), stdin);
if (line == NULL)
break;

line[strlen(line) - 1] = '\0';

pid = fork();
if (pid == 0) {
argv[0] = line;
execve(argv[0], argv, NULL);
}
else
{
wait(NULL);
}
}
return 0;
}

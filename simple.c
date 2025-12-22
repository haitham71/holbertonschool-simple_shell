#include <stdio.h>
#include <stdlib.h>

int main (void)
{
char *argv[] = {"/bin/ls", NULL};

while (1)
{
printf("cisfun$ ");
size_t pid = fork();
if (pid == 0)
{
execve(argv[0],argv ,NULL);
}
else
{
wait(NULL);
}
}

}
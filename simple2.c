#include <stdio.h>
#include <stdlib.h>

int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

while(1)
{
	printf("#cisfun$ ");
	fflush(stdout);

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	break;

	if (nread == 1)
	continue;
}
free(line);
return (0);
}

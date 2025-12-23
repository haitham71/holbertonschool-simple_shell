#include "shell_headers.h"

/**
 * main - Simple shell entry point
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
char *args[64];
FILE *fp;
int status = 0;

fp = get_input_stream(argc, argv);

while (1)
{

display_shell(fp);

nread = getline(&line, &len, fp);
if (nread == -1)
break;

if (nread > 0 && line[nread - 1] == '\n')
line[nread - 1] = '\0';

tokenize(line, args);

if (args[0] == NULL)
continue;

if (strcmp(args[0], "exit") == 0)
break;

if (args[0] != NULL)
{
status = execute_command(args, env);
}
}
clean_output(line, fp);
return(status);
}

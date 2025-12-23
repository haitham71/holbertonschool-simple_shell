#include "shell_headers.h"

/**
 * execute_command - Creates a child process and executes the command
 * @args: Array of arguments (command and its options)
 * @env: Environment variables
 */

void execute_command(char **args, char **env)
{
pid_t pid;

pid = fork();
if (pid == -1)
{
/* If fork fails, print error and return to main loop */
perror("fork");
return;
}

if (pid == 0)
{
/* Inside Child Process */
if (execve(args[0], args, env) == -1)
{
/* Expected error format for the checker */
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
exit(127);
}
}
else
{
/* Inside Parent Process: Wait for child to finish */
wait(NULL);
}
}

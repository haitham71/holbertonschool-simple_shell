#include "shell_headers.h"
/**
 * execute_command - Executes a command if found
 * @args: Array of arguments
 * @env: Environment variables
 */
void execute_command(char **args, char **env)
{
	pid_t pid;
	char *cmd_path;

	cmd_path = find_command_path(args[0], env);
	if (!cmd_path)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, env) == -1)
		{
			perror("./hsh");
			exit(127);
		}
	}
	else
		wait(NULL);

	free(cmd_path);
}

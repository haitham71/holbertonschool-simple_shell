#include "shell_headers.h"
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

/**
 * execute_command - Executes a command
 * @args: Command arguments
 * @env: Environment variables
 *
 * Return: exit status
 */
int execute_command(char **args, char **env)
{
    pid_t pid;
    char *cmd_path;
    int status;

    cmd_path = find_command_path(args[0], env);
    if (!cmd_path)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return (127);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(cmd_path);
        return (127);
    }

    if (pid == 0)
    {
        execve(cmd_path, args, env);
        perror("execve");
        exit(127);
    }
    else
        wait(&status);

    free(cmd_path);
    return (WEXITSTATUS(status));
}

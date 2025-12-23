#include "shell_headers.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/**
 * execute_command - Executes a command with arguments
 * @args: Command arguments
 * @env: Environment variables
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
        return(127);
    }

    if (pid == 0)
    {
        if (execve(cmd_path, args, env) == -1)
        {
            perror("execve");
            exit(127);
        }
    }
    else
    wait(&status);

    free(cmd_path);
    return (WEXITSTATUS(status));
}

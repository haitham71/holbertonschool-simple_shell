#include "shell_headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * execute_command - Creates a child process and executes the command
 * @args: Array of arguments (command and its options)
 * @env: Environment variables
 */
void execute_command(char **args, char **env)
{
    pid_t pid;
    char *cmd_path;

    if (!args[0])
        return;

    cmd_path = find_command_path(args[0]);
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
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            free(cmd_path);
            exit(127);
        }
    }
    else
    {
        wait(NULL);
        free(cmd_path);
    }
}
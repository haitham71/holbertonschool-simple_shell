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
void execute_command(char **args, char **env)
{
    pid_t pid;
    char *cmd_path;

    /* تحقق من وجود الأمر أولاً */
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
        execve(cmd_path, args, env);
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        free(cmd_path);
        exit(127);
    }
    else
    {
        wait(NULL);
    }
    free(cmd_path);
}

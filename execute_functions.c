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

    /* تحقق من PATH قبل fork */
    cmd_path = find_command_path(args[0]);
    if (cmd_path == NULL)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        /* set exit status */
        if (args[0] != NULL)
            exit(127);
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /* Child */
        if (execve(cmd_path, args, env) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            exit(127);
        }
    }
    else
        wait(NULL);
}

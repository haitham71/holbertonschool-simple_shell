#include "shell_headers.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
/**
 * find_command_path - finds full path of a command using PATH
 * @command: command name
 *
 * Return: full path or NULL
 */
char *find_command_path(char *command)
{
    struct stat st;
    char *path, *path_copy, *token, *full_path;

    /*  ^d ^h    ^d   ^e    ^e ^h   ^h    ^e           (/bin/ls  ^e   ^d   ^k) */
    if (stat(command, &st) == 0)
        return (strdup(command));

    path = getenv("PATH");
    if (!path)
        return (NULL);

    path_copy = strdup(path);
    token = strtok(path_copy, ":");

    while (token)
    {
        full_path = malloc(strlen(token) + strlen(command) + 2);
        if (!full_path)
            break;

        sprintf(full_path, "%s/%s", token, command);

        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

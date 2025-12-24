#include "shell_headers.h"

char *find_command_path(char *command, char **env)
{
    char *path_env, *path_copy, *dir, *full_path;
    struct stat st;

    if (command[0] == '/' || command[0] == '.')
    {
        if (stat(command, &st) == 0)
            return (strdup(command));
        return (NULL);
    }

    path_env = get_path_value(env);
    if (!path_env || strlen(path_env) == 0)
        return (NULL);

    path_copy = strdup(path_env);
    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path) break;

        sprintf(full_path, "%s/%s", dir, command);
        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}
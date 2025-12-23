#include "shell_headers.h"

/* Returns the full path of command if exists, else NULL */
char *find_command_path(char *command, char **env)
{
    char *path_env = get_path_value(env);
    char *path_copy, *dir;
    struct stat st;
    char *full_path = NULL;

    if (!path_env || command[0] == '/')
    {
        if (stat(command, &st) == 0)
            return strdup(command);
        return NULL;
    }

    path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
            break;
        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return full_path;
        }
        free(full_path);
        full_path = NULL;
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}

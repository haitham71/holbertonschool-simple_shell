#include "shell_headers.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * find_command_path - Returns full path of command if exists in PATH
 * @command: Command name
 *
 * Return: Full path string (malloc'd) or NULL if not found
 */
char *find_command_path(char *command)
{
    char *path_env = NULL;
    char *path_dup, *dir, *full_path;
    struct stat st;

    path_env = getenv("PATH");  // Allowed if checker يسمح، إذا لا راح نعدل
    if (!path_env || path_env[0] == '\0')
        return (NULL);

    path_dup = strdup(path_env);
    if (!path_dup)
        return (NULL);

    dir = strtok(path_dup, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + 1 + strlen(command) + 1);
        if (!full_path)
        {
            free(path_dup);
            return (NULL);
        }
        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (stat(full_path, &st) == 0)
        {
            free(path_dup);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path_dup);
    return (NULL);
}

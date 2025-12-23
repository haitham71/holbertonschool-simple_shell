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
char *get_path_value(char **env)
{
	int i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

#include "shell_headers.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/**
 * find_command_path - Searches for the command in the PATH
 * @command: The command name
 *
 * Return: Full path if found, NULL if not
 */
char *find_command_path(char *command)
{
    char *path_env, *path_copy, *dir, *full_path;
    struct stat st;

    /* Get PATH environment variable manually from environ */
    extern char **environ;
    int i = 0;
    path_env = NULL;
    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path_env = environ[i] + 5;
            break;
        }
        i++;
    }

    if (!path_env || path_env[0] == '\0')
        return (NULL);

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + 1 + strlen(command) + 1);
        if (!full_path)
            return (NULL);
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
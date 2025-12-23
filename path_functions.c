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

char *find_command_path(char *command, char **env)
{
	char *path, *path_copy, *dir;
	char full_path[1024];
	struct stat st;

	if (stat(command, &st) == 0)
		return (strdup(command));

	path = get_path_value(env);
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

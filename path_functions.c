#include "shell_headers.h"
#include <unistd.h>

/**
 * find_command_path - Finds the full path of a command
 * @command: The command
 * @env: Environment variables
 *
 * Return: Full path or NULL
 */

char *find_command_path(char *command, char **env)
{
	char *path_env, *path_copy, *dir, *full_path;
	size_t len;

	if (!command || *command == '\0')
		return (NULL);

	/* Case: command contains '/' */
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path_env = get_path_value(env);
	if (!path_env || *path_env == '\0')
		path_env = "/bin:/usr/bin";

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		snprintf(full_path, len, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
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

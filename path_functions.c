#include "shell_headers.h"

/**
 * find_command_path - يبحث عن المسار الكامل للأمر
 * @command: الأمر المدخل (مثلاً ls أو /bin/ls)
 * @env: مصفوفة متغيرات البيئة
 * Return: المسار الكامل إذا وجد، أو NULL
 */
char *find_command_path(char *command, char **env)
{
    char *path_env, *path_copy, *dir, *full_path;
    struct stat st;

    if (!command || *command == '\0')
        return (NULL);

    if (strchr(command, '/') != NULL)
    {
        if (stat(command, &st) == 0 && S_ISREG(st.st_mode))
        {
            if (st.st_mode & S_IXUSR)
                return (strdup(command));
        }
        return (NULL);
    }

    path_env = get_path_value(env);
    if (!path_env || *path_env == '\0')
        return (NULL);

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }

        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode))
        {
            if (st.st_mode & S_IXUSR)
            {
                free(path_copy);
                return (full_path);
            }
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

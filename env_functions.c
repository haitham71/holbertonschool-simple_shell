#include "shell_headers.h"

/* Returns the value of PATH from env */
char *get_path_value(char **env)
{
    int i = 0;

    while (env[i])
    {
        if (strncmp(env[i], "PATH", 4) == 0 && env[i][4] == '=')
        return (env[i] + 5);
        
        i++;
    }
    return (NULL); /* PATH غير موجود */
}

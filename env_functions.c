#include "shell_headers.h"

/* Returns the value of PATH from env */
char *get_path_value(char **env)
{
    int i = 0;
    size_t len = 5; /* strlen("PATH=") */

    while (env[i])
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        return (env[i] + len);
        
        i++;
    }
    return NULL; /* PATH غير موجود */
}

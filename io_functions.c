#include "shell_headers.h"

void display_shell(FILE *fp)
{
if (fp == stdin && isatty(STDIN_FILENO))
{
printf("cisfun$ ");
fflush(stdout);
}
}

void clean_output(char *line, FILE *fp)
{
free(line);
if (fp != stdin)
fclose(fp);
return (0);
}
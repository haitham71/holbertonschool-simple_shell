#include "shell_headers.h"

void display_shell(FILE *fp)
{
if (fp == stdin && isatty(STDIN_FILENO))
{
printf("cisfun$ ");
fflush(stdout);
}
}
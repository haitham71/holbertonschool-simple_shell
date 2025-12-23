#ifndef SHELL_HEADERS_H
#define SHELL_HEADERS_H

/*headers calls*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*our functions*/
char *trim_line(char *str);
void tokenize(char *line, char **args);
FILE *get_input_stream(int argc, char **argv);
void execute_command(char **args, char **env);

#endif

#ifndef SHELL_HEADERS_H
#define SHELL_HEADERS_H

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h> /* لازم لـ stat */

/* Our functions */
char *trim_line(char *str);
void tokenize(char *line, char **args);
FILE *get_input_stream(int argc, char **argv);
void execute_command(char **args, char **env);
void display_shell(FILE *fp);
void clean_output(char *line, FILE *fp);
char *get_path_value(char **env);
char *find_command_path(char *command, char **env);
char *get_path_value(char **env);
#endif

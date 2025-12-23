#include "shell_headers.h"

/**
 * trim_line - Removes spaces and tabs from start and end of string
 * @str: String to trim
 *
 * Return: Pointer to trimmed string (or empty string if all spaces)
 */

char *trim_line(char *str)
{
char *start = str;
char *end;

while (*start == ' ' || *start == '\t')
start++;

if (*start == '\0')
return (start);

end = start + strlen(start) - 1;

while (end > start && (*end == ' ' || *end == '\t'))
end--;
*(end + 1) = '\0';
return (start);
}


/**
 * tokenize - Splits a string into tokens based on whitespace
 * @line: The input string to be tokenized
 * @args: Array to store the resulting tokens
 */
void tokenize(char *line, char **args)
{
char *token;
int i = 0;
token = strtok(line, " \t");
while (token != NULL && i < 63)
{
args[i++] = token;
token = strtok(NULL, " \t");
}
args[i] = NULL;
}

/**
 * get_input_stream - Determines if input comes from a file or stdin
 * @argc: Argument count from main
 * @argv: Argument vector from main
 * * Return: Pointer to the open file stream or stdin
 */
FILE *get_input_stream(int argc, char **argv)
{
FILE *fp;

if (argc == 2)
{
fp = fopen(argv[1], "r");
if (fp == NULL)
{
perror(argv[0]);
exit(1);
}
return (fp);
}
return (stdin);
}

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
    while (*start == ' ' || *start == '\t') start++;
    if (*start == '\0') return start;
    end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t')) end--;
    *(end + 1) = '\0';
    return start;
}

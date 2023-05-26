#include "shell.h"
/**
 * strtrim - Trims leading and trailing whitespace from a string.
 * @str: The input string to be trimmed.
 *
 * Return: A pointer to the trimmed string.
 */
char *strtrim(char *str)
{
	char *end;

	while (isspace(*str))
		str++;
	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
		end--;

	*(end + 1) = '\0';

	if (*str == '\0')
		return (NULL);
	return (str);
}

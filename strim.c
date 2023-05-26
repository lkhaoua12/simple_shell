#include "shell.h"
/**
 * strtrim - Trims leading and trailing whitespace from a string.
 * @str: The input string to be trimmed.
 *
 * Return: A pointer to the trimmed string.
 */
char *strtrim(char *str)
{
	char *start = str;
	char *end = str + strlen(str) - 1;

	if (str == NULL)
		return (NULL);

	start = str;
	end = str + strlen(str) - 1;

	while (isspace(*start))
		start++;

	while (end > start && isspace(*end))
		end--;

	*(end + 1) = '\0';
	return (start);
}

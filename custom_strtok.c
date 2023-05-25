#include "shell.h"
/**
 * strtok_custom - Custom implementation of strtok function.
 * @str: The string to be tokenized.
 * @delim: The delimiter used to tokenize the string.
 *
 * Return: Pointer to the next token.
 */
char *strtok_custom(char *str, const char *delim, char **state)
{
	char *token_start, *token_end;

	if (str != NULL)
		*state = str;

	if (*state == NULL || **state == '\0')
		return (NULL);

	token_start = *state;
	token_end = strpbrk(*state, delim);

	if (token_end != NULL)
	{
		*token_end = '\0';
		*state = token_end + 1;
	}
	else
		*state += strlen(*state);

	return (token_start);
}

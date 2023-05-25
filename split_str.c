#include "shell.h"
/**
 * split_string - Splits a string into tokens based on a delimiter.
 * @input: The input string to be split.
 * @delim: The delimiter used to split the string.
 * @arg_num: Pointer to store the number of tokens.
 * Return: Array of strings representing the tokens.
 */
char **split_string(char *input, char *delim, int *arg_num)
{
	char *str = strdup(input);
	char **tokens = NULL;
	char *token = NULL;
	char *state;
	int count = 0;

	if (!str)
	{
		return (NULL);
	}
	token = strtok_custom(str, delim, &state);
	while (token != NULL)
	{
		tokens = realloc(tokens, sizeof(char *) * (count + 1));
		tokens[count] = strdup(token);
		count++;
		token = strtok_custom(NULL, delim, &state);
	}
	tokens = realloc(tokens, sizeof(char *) * (count + 1));
	tokens[count] = NULL;
	*arg_num = count;
	free(str);
	return (tokens);
}

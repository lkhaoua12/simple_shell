#include "shell.h"
/**
 * split_string - Split a string into tokens based on a delimiter
 * @input: The string to split
 * @delim: The delimiter to use for splitting
 * @arg_num: Pointer to store the number of tokens (optional)
 *
 * Return: Array of strings (tokens) or NULL if failed
 */
char **split_string(char *input, char *delim, int *arg_num)
{
	char *str = strdup(input);
	char token[125];
	char **tokens = NULL;
	int i, j, in_word = 0, count = 0;

	if (input == NULL)
	{
		free(str);
		return (NULL);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != *delim)
		{
			if (!in_word)
			{
				j = 0;
				in_word = 1;
				tokens = realloc(tokens, sizeof(char *) * (count + 1));
				token[j] = str[i];
			}
			else
			{
				token[j] = str[i];
			}
			j++;
		}
		else if (in_word)
		{
			in_word = 0;
			token[j] = '\0';
			tokens[count] = strdup(token);
			count++;
		}
	}
	if (in_word)
	{
		in_word = 0;
		token[j] = '\0';
		tokens[count] = strdup(token);
		count++;
	}
	tokens = realloc(tokens, sizeof(char *) * (count + 1));
	tokens[count] = NULL;
	*arg_num = count;
	free(str);
	return (tokens);
}

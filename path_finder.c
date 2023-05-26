#include "shell.h"
/**
 * path_finder - Finds the full path of a command.
 * @command: The command to find the full path for.
 * @envp: The environment variables.
 * Return: A pointer to the full path of the command.
 */
char *path_finder(char *command, char **envp)
{
	char *full_path, *path = NULL, *path_copy, *token, *state;

	(void)envp;
	path = getenv("PATH");
	if (path)
		path_copy = strdup(path);
	if (access(command, X_OK) == 0)
	{
		full_path = strdup(command);
		if (path)
			free(path_copy);
		return (full_path);
	}
	if (path == NULL)
	{
		return (NULL);
	}
	token = strtok_custom(path_copy, ":", &state);
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok_custom(NULL, ":", &state);
	}
	free(path_copy);
	return (NULL);
}


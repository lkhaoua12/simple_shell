#include "shell.h"

char *path_finder(char *command)
{
	char *full_path;
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token;
	char *state = strdup(path_copy);

	if (path == NULL)
	{
		free(path_copy);
		return (NULL);
	}
	if (access(command, X_OK) == 0)
	{
		full_path = strdup(command);
		free(path_copy);
		return (full_path);
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


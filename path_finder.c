#include "shell.h"
/**
 * path_finder - Find the full path of a command in the system's PATH
 * @command: The command to find
 *
 * Return: The full path of the command if found, NULL otherwise
 */
char *path_finder(char *command)
{
	char *path = getenv("PATH");
	char *path_cp = strdup(path);
	char full_path[100];
	char **path_list;
	struct stat st;
	int i, path_found = 0, path_num;

	if (command == NULL)
	{
		free(path_cp);
		return (NULL);
	}
	if (stat(command, &st) == 0)
	{
		free(path_cp);
		return (strdup(command));
	}
	path_list = split_string(path_cp, ":", &path_num);
	if (path_list == NULL)
	{
		free(path_cp);
		return (NULL);
	}
	for (i = 0; path_list[i] != NULL; i++)
	{
		if (!path_found)
		{
			strcpy(full_path, path_list[i]);
			strcat(full_path, "/");
			strcat(full_path, command);
			if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode))
			{
				path_found = 1;
			}
		}
		free(path_list[i]);
	}
	free(path_list);
	free(path_cp);
	return (path_found ? strdup(full_path) : NULL);
}

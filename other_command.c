#include "shell.h"
/**
 * other_command - Finds and returns the appropriate handler.
 * @args_list: The list of command arguments.
 *
 * Return: A pointer to the appropriate handler function.
 */
void (*other_command(char **args_list))(char **, int *, int)
{
	int i;

	handle_command handle[] = {
		{"exit", handle_exit},
		{NULL, NULL}
	};

	for (i = 0; handle[i].command != NULL; i++)
	{
		if (strcmp(handle[i].command, args_list[0]) == 0)
			return (handle[i].handler);
	}
	return (NULL);
}

#include "shell.h"

void (*other_command(char **args_list))(char **)
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
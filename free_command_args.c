#include "shell.h"
/**
 * free_command_args - Frees the memory allocated for command arguments.
 * @command_args: Double pointer to the array of command arguments.
 *
 * This function frees the memory allocated for each command argument in the
 * array and then frees the memory for the array itself.
 */
void free_command_args(char **command_args)
{
	int i;

	for (i = 0; command_args[i]; i++)
		free(command_args[i]);
	free(command_args);
}

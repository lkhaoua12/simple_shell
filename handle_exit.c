#include "shell.h"
/**
 * handle_exit - Handles the "exit" command.
 * @args_list: The list of command arguments.
 * @exit_status: Pointer to the exit status.
 * @command_count: The count of commands executed.
 */
void handle_exit(char **args_list, int *exit_status, int command_count)
{
	if (args_list[1])
	{
		*exit_status = atoi(args_list[1]);
		if ((*exit_status == 0 && strcmp(args_list[1], "0") != 0)
				|| *exit_status < 0)
		{
			fprintf(stderr, "./hsh: %d: exit: Illegal number: %s\n",
				command_count, args_list[1]);
			*exit_status = 2;
		}
	}
	free_command_args(args_list);
	exit(*exit_status);
}

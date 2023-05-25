#include "shell.h"

void handle_exit(char **args_list, int *exit_status)
{
	*exit_status = args_list[1] ? atoi(args_list[1]) : *exit_status;
	free_command_args(args_list);
	exit(*exit_status);
}

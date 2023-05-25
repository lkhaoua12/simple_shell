#include "shell.h"
/**
 * execute_command - Executes a command with the given arguments.
 * @command_args: An array of strings.
 * @program_name: The name of the program executing the command.
 * @command_count: The count of the command being executed.
 * @envp: An array of strings representing the environment variables.
 * Return: None.
 */
void execute_command(char **command_args, char *program_name,
		int command_count, char *envp[], int *exit_status)
{
	pid_t child_pid = fork();

	(void)program_name;
	(void)command_count;
	if (child_pid == 0)
	{
		execve(command_args[0], command_args, envp);
		*exit_status = 127;
	}
	else if (child_pid > 0)
	{
		wait(NULL);
		*exit_status = 0;
	}
	else
	{
		fprintf(stderr, "Fork failed.\n");
	}
}

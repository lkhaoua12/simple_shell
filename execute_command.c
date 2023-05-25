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
	char *full_path, int command_count, char *envp[], int *exit_status)
{
	int status;
	pid_t child_pid = fork(), terminated_pid;
	char error_message[100];

	(void)program_name;
	(void)command_count;
	if (child_pid == 0)
	{
		if (execve(full_path, command_args, envp) == -1)
		{
			snprintf(error_message, sizeof(error_message), "ls: cannot access '%s': %s",
				command_args[0], strerror(errno));
			perror(error_message);
		}
	}
	else
	{
		/* Parent process */
		terminated_pid = waitpid(child_pid, &status, 0);
		if (terminated_pid == -1)
		{
			/* Error occurred while waiting */
			perror("waitpid");
			exit(1);
		}
		else
		{
			if (WEXITSTATUS(status))
			{
				/* child procces exited */
				*exit_status = WEXITSTATUS(status);
			}
			else if (WIFEXITED(status))
			{
				/* Child process return normally */
				*exit_status = WTERMSIG(status);
			}
		}
	}
}

#include "shell.h"
/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(void)
{
	if (isatty(fileno(stdin)))
	{
		printf("$ ");
		fflush(stdout);
	}
}
/**
 * read_input - Reads input from stdin.
 * Return: The input string, or NULL on failure or EOF.
 */
char *read_input(void)
{
	char *input = NULL;
	size_t input_length = 0;
	ssize_t bytes_read = getline(&input, &input_length, stdin);

	if (bytes_read == -1)
	{
		if (feof(stdin))
		{
			if (isatty(fileno(stdin)))
				printf("\n");
			return (NULL);
		}
		else
		{
			perror("");
			free(input);
			return (NULL);
		}
	}

	if (*input == '\n' || *strtrim(input) == '\0')
	{
		free(input);
		return (NULL);
	}

	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';

	trimString(input);
	return (input);
}

/**
 * command_handler - Handles the execution of commands.
 * @args_list: The list of command arguments.
 * @exit_status: Pointer to the exit status variable.
 * @command_count: The command count.
 * @argv: The program argument vector.
 * @envp: The program environment variables.
 */
void command_handler(char **args_list, int *exit_status,
		int command_count, char **argv, char **envp)
{
	char *full_path = path_finder(args_list[0]);
	void (*handler)(char **, int *, int);

	if (full_path == NULL)
	{
		handler = other_command(args_list);
		if (handler != NULL)
		{
			handler(args_list, exit_status, command_count);
		}
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0],
				command_count, args_list[0]);
			free_command_args(args_list);
			*exit_status = 127;
		}
	}
	else
	{
		execute_command(args_list, argv[0], full_path,
				command_count, envp, exit_status);
		free(full_path);
		free_command_args(args_list);
	}
}
/**
 * main - Entry point of the shell program.
 * @argc: The argument count.
 * @argv: The argument vector.
 * @envp: The environment variables.
 *
 * Return: The exit status of the shell.
 */
int main(int argc, char **argv, char **envp)
{
	char **args_list = NULL;
	char *input = NULL;
	int exit_status = 0, args_num, command_count = 1;
	(void)argc;

	while (1)
	{
		print_prompt();
		input = read_input();
		if (input == NULL)
		{
			break;
		}
		args_list = split_string(input, " ", &args_num);
		free(input);
		input = NULL;
		if (args_list == NULL || *args_list[0] == '\0')
		{
			exit_status = 127;
			command_count++;
			continue;
		}
		command_handler(args_list, &exit_status, command_count, argv, envp);
		command_count++;
	}

	free(input);
	return (exit_status);
}

#include "shell.h"
/**
 * print_prompt - Prints the shell prompt if input is from the terminal.
 */
void print_prompt(void)
{
	if (isatty(fileno(stdin)))
	{
		printf("$ ");
	}
}
/**
 * read_input - Reads the input from the user and returns the input string.
 * @end_of_file: int to store if end_of_file reached.
 * Return: The input string entered by the user.
 */
char *read_input(int *end_of_file)
{
	char *input = NULL;
	size_t input_length;
	int bytes_read;

	bytes_read = getline(&input, &input_length, stdin);

	if (bytes_read == -1)
	{
		/* check if end of file reached */
		if (feof(stdin))
		{
			if (isatty(fileno(stdin)))
				printf("\n");
			*end_of_file = 1;
			return (NULL);
		}
		else
		{
			perror("");
			return (NULL);
		}
	}
	/* get rid of the new line at the end */
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';

	input = strtrim(input);
	if (*input == '\0')
	{
		return (NULL);
	}
	return (input);
}
/**
 * handle_command - Handles the execution of a command.
 * @args_list: The list of command arguments.
 * @exit_status: Pointer to the exit status.
 * @command_count: The count of commands executed.
 * @envp: The environment variables.
 * @program_name: The name of the program.
 */
void command_handler(char **args_list, int *exit_status, int command_count,
			char **envp, char *program_name)
{
	void (*handler)(char **, int *, int);
	char *full_path = path_finder(args_list[0], envp);

	if (full_path == NULL)
	{
		handler = other_command(args_list);
		if (handler != NULL)
		{
			handler(args_list, exit_status, command_count);
		}
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				program_name, command_count, args_list[0]);
			free_command_args(args_list);
			*exit_status = 127;
		}
	}
	else
	{
		execute_command(args_list, program_name, full_path,
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
 * Return: The exit status of the shell program.
 */
int main(int argc, char **argv, char **envp)
{
	char **args_list = NULL;
	int command_count = 1, exit_status = 0, args_num;
	int end_of_file = 0;
	char *input = NULL;

	(void)argc;
	while (1)
	{
		fflush(stdout);
		print_prompt();

		input = read_input(&end_of_file);
		if (input == NULL)
		{
			if (end_of_file)
				break;
			continue;
		}
		args_list = split_string(input, " ", &args_num);
		free(input);
		if (args_list == NULL || *args_list[0] == '\0')
		{
			exit_status = 127;
			command_count++;
			continue;
		}

		command_handler(args_list, &exit_status, command_count, envp, argv[0]);
		command_count++;
	}
	return (exit_status);
}

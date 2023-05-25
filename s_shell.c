#include "shell.h"


int main(int argc, char **argv, char **envp)
{
	char **args_list = NULL, *input = NULL, *full_path;
	size_t input_length;
	int bytes_read;
	int command_count = 1, exit_status = 0, args_num;
	void (*handler)(char **);
	(void)argc;
	while (1)
	{
		fflush(stdout);
		/* check if input from stdin*/
		if (isatty(fileno(stdin)))
		{
			printf("$ ");
		}
		bytes_read = getline(&input, &input_length, stdin);
		if (bytes_read == -1)
		{
			/* chek if end of file reached*/
			if (feof(stdin))
			{
				if (isatty(fileno(stdin)))
					printf("\n");
				break;
			}
			else
			{
				perror("");
				free(input);
				command_count++;
				exit_status = 127;
				continue;
			}	
		}
		if (*input == '\n')
		{
			free(input);
			input = NULL;
			continue;
		}
		/* get rid of the new line at the end*/
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';
		args_list = split_string(input, " ", &args_num);
		free(input);
		input = NULL;
		if (args_list == NULL)
		{
			exit_status = 127;
			command_count++;
			continue;
		}	
		/* find the full path of the command */
		full_path = path_finder(args_list[0]);
		if (full_path == NULL)
		{
			handler = other_command(args_list);
			if (handler != NULL)
			{
				handler(args_list);
			}
			else
			{
				fprintf(stderr, "%s: %d: %s: not found\n", argv[0],
				command_count, args_list[0]);
				free_command_args(args_list);
				exit_status = 127;
				command_count++;
				continue;
			}
		}
		else
		{
			execute_command(args_list, argv[0], full_path, command_count, envp, &exit_status);
			free(full_path);
			free_command_args(args_list);
			command_count++;
		}
	}
	free(input);
	return (exit_status);
}

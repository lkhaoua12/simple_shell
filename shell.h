#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

typedef struct hl{
	char *command;
	void (*handler)(char **args_list, int *exit_status);
}handle_command;
char **split_string(char *str, char *delim, int *words_num);
char *path_finder(char *command);
void execute_command(char **command_args, char *program_name,
		char *full_path, int command_count, char *envp[], int *exit_status);
void free_command_args(char **command_args);
void handle_noninteractive_mode(char *program_name, char *envp[]);
char *strtok_custom(char *str, const char *delim, char **state);
void handle_exit(char **args_list, int *exit_status);
void (*other_command(char **args_list))(char **, int *);
char *strtrim(char *str);


#endif

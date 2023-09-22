#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "main.h"

/**
 * display_prompt - is defined to print a simple shell prompt
 * Return: null
 */
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/**
 * remove_newline - remove the trailing newline character
 *
 * @str: pointer to a character array
 * Return: null
 */
void remove_newline(char *str)
{
	str[strcspn(str, "\n")] = '\0';
}
/**
 * tokenize_input - takes a user input string
 *
 * @input: pointer array of character
 * @args: pointers store the tokenized arguments
 * Return: number of tokens arguments
 */
int tokenize_input(char *input, char **args)
{
	char *token = strtok(input, " ");
	int arg_count = 0;

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
	return (arg_count);
}
/**
 * check_command_exists - checks if a command exists in the PATH
 *
 * @command: the command to check
 * Return: 1 if the command exists, 0 otherwise
 */
int check_command_exists(char *command)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char full_path[MAX_INPUT_LENGTH];

		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
			if (access(full_path, F_OK) == 0)
			{
				return (1);
			}
			token = strtok(NULL, ":");
	}
	return (0);
}
/**
 * execute_command - represents the list of command arguments to execute
 *
 * @args: pointers array of character
 * Return: null
 */
void execute_command(char **args)
{
	pid_t pid;

	if (strcmp(args[0], "exit") == 0)
	{
		handle_exit(args);
		return;
	}
	if (!check_command_exists(args[0]))
	{
		fprintf(stderr, "simple_shell: %s: command not found\n", args[0]);
		return;
	}
	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		execvp(args[0], args);

		fprintf(stderr, "simple_shell: %s: command not found\n", args[0]);
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}

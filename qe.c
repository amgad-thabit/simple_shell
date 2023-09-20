#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

/**
 * display_prompt - is defined to print a simple shell prompt
 * Return: null
 */
void display_prompt(void)
{
	printf("$ ");
}
/**
 * remove_newline - remove the trailing newline character
 *
 * @str: pointer to a character array
 * Return: null
 */
void remove_newline(char *str)
{
	str[strlen(str) - 1] = '\0';
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
		printf("Goodbye!\n");
		exit(0);
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
/**
 * main - entry point of the program
 *
 * Return: 0
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_INPUT_LENGTH / 2];
	int arg_count;

	while (1)
	{
		display_prompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\nGoodbye!\n");
			break;
		}
		remove_newline(input);
		if (strlen(input) == 0)
		{
			continue;
		}
		arg_count = tokenize_input(input, args);

		if (arg_count > 0)
		{
			execute_command(args);
		}
	}
	return (0);
}


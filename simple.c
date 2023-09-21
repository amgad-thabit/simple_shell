#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

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
		wait(NULL);
	}
	return (0);
}

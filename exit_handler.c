#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * handle_exit - print the exit status code of the last executed command
 *
 * @args: pointer to a character array
 * Return: null
 */
void handle_exit(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);

		if (status == 0 && strcmp(args[1], "0") != 0)
		{
			fprintf(stderr, "shell: exit: %s: numeric argument\n", args[1]);
			return;
		}
	}
	printf("%d\n", status);
	exit(status);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT 1024

int is_simple_command(const char *input)
{
	size_t len = strlen(input);
	size_t i;

	for (i = 0; i < len; i++)
	{
		if (input[i] == ' ' || input[i] == ';' || input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			return (0);
		}
	}
	return (1);
}

int main(void)
{
	char buffer[MAX_INPUT];
	size_t length;
	pid_t pid;
	int status;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		length = strlen(buffer);

		if (length > 0 && buffer[length - 1] == '\n')
			buffer[length - 1] = '\0';
		if (!is_simple_command(buffer))
		{
			printf("Unsupported command: %s\n", buffer);
			continue;
		}
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execlp(buffer, buffer, NULL);
			fprintf(stderr, "Error: %s: %s\n", buffer, strerror(errno));
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				printf("Command not found: %s\n", buffer);
			}
		}
	}

    return (0);
}


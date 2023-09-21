#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char command[256];
	char prompt[] = "MyShell> ";
	pid_t pid;
	int status;

	while (1)
	{
		printf("%s", prompt);
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("Error reading input");
				exit(1);
			}
		}
		command[strcspn(command, "\n")] = '\0';
		pid = fork();

		if (pid == -1)
		{
			perror("Fork error");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execlp(command, command, (char *)NULL) == -1)
			{
				perror("Command not found");
				exit(1);
			}
		} else
		{
			waitpid(pid, &status, 0);

			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				fprintf(stderr, "Command exited with non-zero status\n");
			}
		}
	}
	return (0);
}

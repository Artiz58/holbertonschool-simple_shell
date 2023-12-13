#include "shell.h"

void execute_command(char **args)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}

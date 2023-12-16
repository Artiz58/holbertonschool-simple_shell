#include "shell.h"
/**
 * execute_command - executes the given command with arguments
 * @full_path: full path to the executable
 * @args: array of command-line arguments
 */
void execute_command(char *full_path, char *args[])
{
	pid_t pid;
	int status;

	pid = fork();   /* Create a child process */
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{   /* Code executed by the child process */
		if (execve(full_path, args, environ) == -1)
		{
			printf("Command not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{    /* Code executed by the parent process */
		waitpid(pid, &status, 0);       /* Wait for the child process to finish */
	}
}

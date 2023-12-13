#include "shell.h"
/**
 * execute_command - Execute a command in a child process
 * @args: An array of strings representing the command and its arguments
 *
 * This function forks a child process and executes the specified command in
 * the child process.
 */
void execute_command(char *command)
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		if (execlp(command, command, (char *)NULL) == -1)
		{
			perror("Error al ejecutar el comando");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error al crear el proceso hijo");
	}
	else
	{

		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
			(void)wpid;
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

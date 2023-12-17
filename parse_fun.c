#include "shell.h"
/**
 * parse_command - Parse the command into tokens
 * @command: Command to be parsed
 * @args: Array to store command tokens
 * Return: Number of tokens
 */
int parse_command(char *command, char *args[])
{
	int num_tokens = 0;
	char *token = strtok(command, " ");

	while (token != NULL && num_tokens < MAX_ARGS - 1)
	{
		args[num_tokens++] = token;
		token = strtok(NULL, " ");
	}
	args[num_tokens] = NULL;
	return (num_tokens);
}

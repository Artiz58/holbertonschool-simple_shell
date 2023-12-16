#include "shell.h"
/**
 * main - main function of the shell
 * Return: 0 when the program ends
 */
int main(void)
{
	int num_tokens = 0, _prompt = isatty(fileno(stdin));
	char *args[MAX_ARGS], *command = NULL, *token;
	size_t buffer = 0, length;
	char *path[] = {"/usr/local/bin/", "/usr/bin/", "/bin/",
					"/usr/local/games/", "/usr/games/"};
while (1)
{
	if (_prompt)
	{
		printf("($) ");
	}
	if (getline(&command, &buffer, stdin) != -1)
	{
	length = strlen(command);
	if (command[length - 1] == '\n')
		command[length - 1] = '\0';
	if (strcmp(command, "") == 0)
		continue;
	if (strcmp(command, "exit") == 0)
	{
		free(command);
		return (0);
	}
	num_tokens = 0;
	token = strtok(command, " ");
	while (token != NULL && num_tokens < MAX_ARGS - 1)
	{
		args[num_tokens++] = token;
		token = strtok(NULL, " ");
	}
	args[num_tokens] = NULL;
	if (num_tokens == 0)
		continue;
	if (check_access(args[0], args, path))
	{
		execute_command(args[0], args);
	}
	else
	{
	printf("Command not found\n");
			continue;
	}
}
	else
	{
	if (!_prompt)
		break;
	printf("\n");
		break;
	}
	}
	free(command);
	return (0);
}

#include "shell.h"
/**
 * main - Main function of the shell
 * Return: 0 when the program ends
 */
int main(void)
{
	int num_tokens;
	char *args[MAX_ARGS], *command = NULL;
	size_t buffer = 0, length;
	char *path[] = {"/usr/local/bin/", "/usr/bin/", "/bin/",
					"/usr/local/games/", "/usr/games/"};
	signal(SIGINT, sigintHandler);

	while (1)
	{
		display_prompt();
		if (get_command(&command, &buffer) != -1)
		{
		length = strlen(command);
		if (length > 0 && command[length - 1] == '\n')
			command[length - 1] = '\0';
		if (strcmp(command, "") == 0)
			continue;
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			return (0);
		}
		num_tokens = parse_command(command, args);
		if (num_tokens == 0)
			continue;
		if (check_access(args[0], args, path))
			execute_command(args[0], args);
		else
			printf("Command not found\n");
		}
		else
		{
			break;
		}
	}
	free(command);
	return (0);
}

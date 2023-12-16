#include "shell.h"
/**
 * main - main function of the shell
 * Return: 0 when the program ends
 */
int main()
{
	int num_tokens;
	size_t i;
	char *args[MAX_ARGS];
	char *command = NULL;
	char *token;
	size_t buffer = 0;
	size_t length;
	char *path[] = {"/usr/local/bin/",
		"/usr/bin/",
		"/bin/",
		"/usr/local/games/",
		"/usr/games/"};
	char full_path[MAX_ARGS];
	int _prompt = isatty(fileno(stdin));

	while (1) {
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

			if (access(args[0], X_OK) == 0)
			{
				for (i = 0; i < 5; i++)
				{
					execve(command, args, environ);
					break;
				}
			}
			else
			{
				for (i = 0; i < 5; i++)
				{
					strcpy(full_path, path[i]);
					strcat(full_path, args[0]);

					if (access(full_path, X_OK) == 0)
						break;
				}
			}

			if (access(full_path, X_OK) == -1)
			{
				printf("Command not found\n");
				continue;
			}

			execute_command(full_path, args);
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

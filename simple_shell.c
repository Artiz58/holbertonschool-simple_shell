#include "shell.h"
/**
 * main - Simple shell program
 *
 * This is a simple shell program that allows the user to enter commands.
 * It supports executing commands and the "which" command for checking file
 * existence.
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t length;

	while (1)
	{
		printf("($) ");
		getline(&buffer, &buffer_size, stdin);

		length = strlen(buffer);
		if (length > 0 && buffer[length - 1] == '\n')
		{
			buffer[length - 1] = '\0';
		}

		if (strcmp(buffer, "exit") == 0)
		{
			break;
		}

		parse_and_execute(buffer);
	}
	free(buffer);

	return (0);
}

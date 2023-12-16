#include "shell.h"
/**
 * check_access - Check if the command has execute permission.
 * Search for the command in the specified paths.
 *
 * @command: The command to check for execute permission.
 * @args: The arguments passed to the command.
 * @path: The array of paths to search for the command.
 * Return: 1 if access is granted, 0 otherwise.
 */
int check_access(char *command, char *args[], char *path[])
{
	char full_path[MAX_ARGS];
	size_t i;

	if (access(command, X_OK) == 0)
	{
		return (1);
	}
	else
	{
		for (i = 0; i < 5; i++)
		{
			strcpy(full_path, path[i]);
			strcat(full_path, command);

			if (access(full_path, X_OK) == 0)
			{
				/* Update args with the full path */
				args[0] = strdup(full_path);
				return (1);
			}
		}
	}
	return (0);
}

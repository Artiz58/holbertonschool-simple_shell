#include <stdio.h>
#include "shell.h"

/**
 * error- found not excectubale command
 * @args: array of arguments from get_tokens
 */

void error(char **args)
{
	fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
	exit(127);
}


/**
 * main - Simple System Shell (sh)
 * Return: 0 on succes
 */

int main(void)
{
	char *str_line = NULL;
	size_t len = 0;
	ssize_t read_bytes;
	int on = 1;
	char **args;

	while (on != 0)
	{
		if (isatty(fileno(stdin)))
			printf("($) ");
		read_bytes = getline(&str_line, &len, stdin); /* stdin into str_line */

		if (read_bytes == -1) /* check if getline is succesfull */
		{
			if (isatty(fileno(stdin)))
				printf("\n");
			on = 0;
		}
		else
		{
			remove_newline(&str_line, &read_bytes);
			if (strcmp(str_line, "exit") == 0) /* check if user put Exit */
				on = 0;
			else
			{
				args = get_tokens(str_line); /* makes tokens and args array with mallocs */
				if ((white_spaces(args, str_line)) == 0) /* if white spaces only */
					return (main());
				if (access(args[0], X_OK) == 0) /*!args */
					my_exe(args, environ);
				else
					get_path(args, environ); /*!args */
				if (access(args[0], X_OK) != 0)
					error(args);
				free_array(args);
			}
		}
	}
	free(str_line);/* always free the str_line form stdin */
	return (0);
}

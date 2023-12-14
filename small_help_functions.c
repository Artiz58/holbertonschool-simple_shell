#include <stdio.h>
#include "shell.h"

/**
 * white_spaces - checks if args is null, has only white spaces
 * @args: array from get_tokens, from main
 * @str_line: string from main, from stdin
 * Return: 0 if args was null(white spaces only)
 */

int white_spaces(char **args, char *str_line)
{
	if (args[0] == NULL) /* white spaces only */
	{
		free(str_line);
		free(args);
		return (0);
	}

	return (-1);
}

/**
 * free_array - free the args array
 * @args : array from get tokens, tokenization of str_line
 */

void free_array(char **args)
{
	int i = 0;

	for (i = 0; args[i] != NULL; i++) /* free the array & indxs */
		free(args[i]);
	free(args);
}

/**
 * remove_newline - remove new line from str_line
 * @str_line: string from main, stdin
 * @read_bytes: total chars read for str_line
 */

void remove_newline(char **str_line, ssize_t *read_bytes)
{
	if ((*str_line)[strlen(*str_line) - 1] == '\n')
	{
		(*str_line)[strlen(*str_line) - 1] = '\0'; /* removed \n with \0 */
		(*read_bytes)--; /* -1 to the old \n byte count */
	}
}

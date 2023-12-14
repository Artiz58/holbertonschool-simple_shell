#include "shell.h"

/**
 * has_only_white_spaces - checks if args is null or has only white spaces
 * @args: array from get_tokens, from main
 * @str_line: string from main, from stdin
 * Return: 0 if args was null (or white spaces only), -1 otherwise
 */
int white_spaces(char **args, char *str_line)
{
    if (args[0] == NULL || strspn(str_line, " \t\n") == strlen(str_line))
    {
        free(str_line);
        free(args);
        return (0); /* white spaces only */
    }

    return (-1);
}

/**
 * free_tokens - free the args array
 * @args: array from get_tokens, tokenization of str_line
 */
void free_tokens(char **args)
{
	int i;

    for (i = 0; args[i] != NULL; i++)
    {
        free(args[i]);
    }
    free(args);
}

/**
 * remove_newline - remove new line from str_line
 * @str_line: string from main, stdin
 */
void remove_newline(char *str_line, ssize_t *read_bytes)
{
    size_t length = strlen(str_line);

    if (length > 0 && str_line[length - 1] == '\n')
    {
        str_line[length - 1] = '\0';
        (*read_bytes)--;
    }
}

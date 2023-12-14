#include "shell.h"

/**
 * error - Print error message and exit
 * @args: Array of arguments from get_tokens
 */
void error(char **args)
{
    fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
    exit(127);
}

/**
 * display_prompt - Display shell prompt if input is from terminal
 */
void display_prompt(void)
{
    if (isatty(fileno(stdin)))
        printf("($) ");
}

/**
 * process_input - Process user input
 * @str_line: Pointer to input string
 * @len: Length of the input string
 * @on: Pointer to flag indicating whether the shell should continue running
 */

extern char **environ;

void process_input(char *str_line, size_t len, int *on)
{
    ssize_t read_bytes;
    char **args;

    display_prompt();
    read_bytes = getline(&str_line, &len, stdin);

    if (read_bytes == -1)
    {
        if (isatty(fileno(stdin)))
            printf("\n");
        *on = 0;
    }
    else
    {
        remove_newline(str_line, &read_bytes);
        if (strcmp(str_line, "exit") == 0)
            *on = 0;
        else
        {
            args = get_tokens(str_line);
            if (white_spaces(args, str_line) == 0)
                process_input(str_line, len, on);
            if (access(args[0], X_OK) == 0)
                my_exe(args, environ);
            else
            {
                get_path(args, environ);
                if (access(args[0], X_OK) != 0)
                    error(args);
            }
            free_array(args);
        }
    }
}

/**
 * main - Simple System Shell (sh)
 * Return: 0 on success
 */
int main(void)
{
    char *str_line = NULL;
    size_t len = 0;
    int on = 1;

    while (on != 0)
    {
        process_input(str_line, len, &on);
    }

    free(str_line);
    return (0);
}

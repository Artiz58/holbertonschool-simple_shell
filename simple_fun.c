#include "shell.h"
/**
 * display_prompt - Display shell prompt
 */
void display_prompt(void)
{
	if (isatty(fileno(stdin)))
	{
		printf("($) ");
	}
}
/**
 * get_command - Read a line of input from the user
 * @buffer: Buffer to store the input
 * @size: Size of the buffer
 * Return: Number of characters read
 */
ssize_t get_command(char **buffer, size_t *size)
{
	return (getline(buffer, size, stdin));
}
/**
 * sigintHandler - Signal handler for SIGINT (Ctrl + C).
 * This function is triggered when the program receives
 * the SIGINT signal, typically generated by pressing Ctrl + C.
 * It prints an exit message and terminates the program.
 */
void sigintHandler(void)
{
	printf("\n");
	exit(0);
}

#include "shell.h"
/**
 * check_command - Check if a file exists
 * @command: The name of the command or file to check
 *
 * This function checks if the specified file exists and prints a message
 * accordingly.
 */
void check_command(char *command)
{
	if (access(command, F_OK) == 0)
		printf("%s: FOUND THE FILE\n", command);
	else
		printf("%s: FILE DOESN'T EXIST\n", command);
}

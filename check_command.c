#include "shell.h"

void check_command(char *command)
{
	if (access(command, F_OK) == 0)
		printf("%s: FOUND THE FILE\n", command);
	else
		printf("%s: FILE DOESN'T EXIST\n", command);
}

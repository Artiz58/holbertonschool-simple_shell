#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void check_command(char *command)
{
	if (access(command, F_OK) == 0)
		printf("%s: FOUND THE FILE\n", command);
	else
		printf("%s: FILE DOESN'T EXIST\n", command);
}

int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	char *token;

	while(1)
	{
		printf("($) ");
		getline(&buffer, &buffer_size, stdin);
		token = strtok(buffer, " \t\n");
		if (strcmp(token, "which") == 0)
		{
			token = strtok(NULL, " \t\n");
			while (token)
			{
				check_command(token);
				token = strtok(NULL, " \t\n");
			}
		}
		else
		{
			printf("COMMAND DOSEN'T EXIST\n");
		}
	}
	return (0);
}

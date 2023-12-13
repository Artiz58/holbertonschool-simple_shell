#include "shell.h"

void parse_and_execute(char *input)
{
	int i = 0;
	char *token;
	char **args = malloc(sizeof(char *) * 1024);

	token = strtok(input, " \t\n");
	while (token)
	{
		args[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	args[i] = NULL;

	if (i > 0)
	{
		if (strcmp(args[0], "which") == 0)
		{
            /* "which" command */
			int j = 1;
			while (args[j])
			{
				check_command(args[j]);
				j++;
			}
		}
		else
		{
			execute_command(args);
		}
	}

	free(args);
}

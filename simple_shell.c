#include "shell.h"

int main(void)
{
	size_t buf_size = 0;
	char *buf = NULL;
	char *token;
	int status, i = 0;
	char **array;

	pid_t child_pid;

	while (1)
	{
	printf("($) ");
	getline(&buf, &buf_size, stdin);
	token = strtok(buf, "\t\n");
	array = malloc(sizeof(char *) * 1024);

	while (token)
	{
		array[i] = token;
		token = strtok(NULL, "\t\n");
		i++;
	}
		array[i] = NULL;
		child_pid = fork();

	if (child_pid == 0)
	{
		if (execve (array[0], array, NULL) == -1)
			perror("Error:");
    }
	else
	{
        wait(&status);
	}
	i = 0;
	free(array);
    }
return (0);
}

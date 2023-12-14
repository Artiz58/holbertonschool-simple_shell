#include "shell.h"

/**
 * get_tokens - tokenizes str_line, stores it in array
 * @str_line: string from main, from stdin
 * Return: pointer of array
 */

char **get_tokens(char *str_line)
{
	char **array;
	int tok_count = 0;
	char *token, *str_line_dup;

	str_line_dup = strdup(str_line);/* we need dup to count tokens */
	token = strtok(str_line_dup, " ");

	while (token != NULL)
	{
		tok_count++;
		token = strtok(NULL, " "); /* next token */
	}

	free(str_line_dup);
	array = malloc((tok_count + 1) * sizeof(char *));/* making size for indexes */

	if (array == NULL)
		return (NULL);

	token = strtok(str_line, " "); /* original str to tokenize */
	tok_count = 0;

	while (token != NULL)
	{
		array[tok_count] = strdup(token); /* dup tokens into args,does malloc also*/
		tok_count++;
		token = strtok(NULL, " "); /* next token */
	}
	array[tok_count] = NULL;/* last index of args */
	return (array); /* sending array, args in main receives it */
}

/**
 * get_path - pairs args[0] with possible paths
 * @args : array from tokenization of get_tokens of str_line
 * @environ : golbal variable from system
 */

void get_path(char **args, char **environ)
{
	char path[][30] = {"/usr/local/bin/", /* all possible paths */
		"/usr/bin/",
		"/bin/",
		"/usr/local/games/",
		"/usr/games/"};
	int i;

	for (i = 0; i < 5; i++) /*iterate path and concatenate with args[0]*/
	{
		char *full_path = malloc(strlen(path[i]) + strlen(args[0]) + 1);

		if (full_path == NULL) /* verify if malloc is succesful */
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		strcpy(full_path, path[i]);
		strcat(full_path, args[0]);

		if (access(full_path, X_OK) == 0) /* verify if path is executable */
		{
			free(args[0]);
			args[0] = strdup(full_path);

			my_exe(args, environ);
			free(full_path);
			break;
		}
		free(full_path); /* done the full path, args[0] has full now */
	}
}

/**
 * my_exe - function that creates forks and executes
 * @args: array from get_tokens
 * @environ: global variable of system.
 */

void my_exe(char **args, char **environ)
{
	pid_t pid;

	pid = fork();

	if (pid == -1)/* child wasn't process and it couldn't work */
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)/* child process is the current process in work */
	{
		execve(args[0], args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);/* parent process suspended until the child finishes */
	}

}

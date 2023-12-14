#include "shell.h"
#include <stdio.h>

/**
 * env_path - gets PATH form environ and makes array of paths
 * @environ: enviromental var from system
 * Return: pointer of array for paths
 */

char **env_path(char **environ)
{
	int i, j = 0, token_count = 0;
	char *path, *token, *path_dup;
	char **env_path;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strstr(environ[i], "PATH=") == environ[i])
		{
			path = strdup(environ[i]);
			path_dup = strdup(path);
			token = strtok(path_dup, ":");
			while (token != NULL)
			{
				token_count++;
				token = strtok(NULL, ":");
			}
			free(path_dup);
			env_path = malloc((token_count + 1) * sizeof(char *));
			token = strtok(path, ":");
			while (token != NULL)
			{
				/* Allocate memory for the token and '/' */
				env_path[j] = malloc(strlen(token) + 2);
				strcpy(env_path[j], token);
				strcat(env_path[j], "/"); /* Add '/' at the end */
				j++;
				token = strtok(NULL, ":");
			}

			env_path[j] = NULL;
		}
	}
	free(path);
	return (env_path);
}

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
 * get_path - Concat args[0] with possible paths
 * @args : array from tokenization of get_tokens of str_line
 * @environ : golbal variable from system
 */

void get_path(char **args, char **environ)
{
	char **path;
	char *full_path;
	int i, did_path = 0;

	path = env_path(environ);
	for (i = 0; path[i] != NULL; i++) /*iterate path and concat args[0]*/
	{
		full_path = malloc(strlen(path[i]) + strlen(args[0]) + 1);

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
			free_array(path);
			did_path = 1;
			break;
		}
		free(full_path); /* done the full path, args[0] has full now */

	}
	if (did_path == 0)
		free_array(path);
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

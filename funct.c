#include "shell.h"

/**
 * env_path - gets PATH from environ and makes an array of paths
 * @environ: environmental variable from the system
 * Return: pointer to the array of paths
 */
char **env_path(char **environ) {
    char *path_env = NULL;
    char *token, *token_dup;
    char **env_path;
    int token_count = 0, i;

    while (*environ) {
        if (strncmp(*environ, "PATH=", 5) == 0) {
            path_env = *environ + 5;
            break;
        }
        environ++;
    }

    if (!path_env)
        return NULL;

    token_dup = strdup(path_env);
    if (!token_dup)
        return NULL;

    token = strtok(token_dup, ":");
    while (token != NULL) {
        token_count++;
        token = strtok(NULL, ":");
    }

    free(token_dup);

    env_path = malloc((token_count + 1) * sizeof(char *));
    if (!env_path)
        return NULL;

    token_dup = strdup(path_env);
    if (!token_dup) {
        free(env_path);
        return NULL;
    }

    token = strtok(token_dup, ":");
    for (i = 0; i < token_count; i++) {
        env_path[i] = malloc(strlen(token) + 2);
        if (!env_path[i]) {
            free_array(env_path);
            free(token_dup);
            return NULL;
        }
        strcpy(env_path[i], token);
        strcat(env_path[i], "/");
        token = strtok(NULL, ":");
    }

    env_path[token_count] = NULL;
    free(token_dup);

    return env_path;
}

/**
 * get_tokens - tokenizes str_line, stores it in an array
 * @str_line: string from main, from stdin
 * Return: pointer to the array of tokens
 */
char **get_tokens(char *str_line) {
    char **array;
    char *token, *token_dup;
    int tok_count = 0, i;

    token_dup = strdup(str_line);
    if (!token_dup)
        return NULL;

    token = strtok(token_dup, " ");
    while (token != NULL) {
        tok_count++;
        token = strtok(NULL, " ");
    }

    free(token_dup);

    array = malloc((tok_count + 1) * sizeof(char *));
    if (!array)
        return NULL;

    token_dup = strdup(str_line);
    if (!token_dup) {
        free(array);
        return NULL;
    }

    token = strtok(token_dup, " ");
    for (i = 0; i < tok_count; i++) {
        array[i] = strdup(token);
        if (!array[i]) {
            free_array(array);
            free(token_dup);
            return NULL;
        }
        token = strtok(NULL, " ");
    }

    array[tok_count] = NULL;
    free(token_dup);

    return array;
}

/**
 * get_path - Concatenate args[0] with possible paths
 * @args: array from tokenization of get_tokens of str_line
 * @environ: global variable from the system
 */
void get_path(char **args, char **environ) {
    char **path;
    char *full_path;
    int did_path = 0, i;

    path = env_path(environ);

    if (!path)
        return;

    for (i = 0; path[i] != NULL; i++) {
        full_path = malloc(strlen(path[i]) + strlen(args[0]) + 1);

        if (!full_path) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        sprintf(full_path, "%s/%s", path[i], args[0]);

        if (access(full_path, X_OK) == 0) {
            free(args[0]);
            args[0] = strdup(full_path);
            my_exe(args, environ);
            free(full_path);
            free_array(path);
            did_path = 1;
            break;
        }

        free(full_path);
    }

    if (did_path == 0)
        free_array(path);
}

/**
 * my_exe - function that creates forks and executes
 * @args: array from get_tokens
 * @environ: global variable of the system
 */
void my_exe(char **args, char **environ) {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        execve(args[0], args, environ);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

void free_array(char **arr) {
	int i;

    for (i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}

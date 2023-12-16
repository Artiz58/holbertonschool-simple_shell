#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARGS 64

extern char **environ;

void read_command(char **command) {
    size_t bufsize = 0;
    ssize_t read_bytes;

    if(isatty(fileno(stdin)))
        printf("($) ");
    read_bytes = getline(command, &bufsize, stdin);

    if (read_bytes == -1) {
        exit(EXIT_FAILURE);
    }

    /* Remove newline character if present */
    if ((*command)[read_bytes - 1] == '\n') {
        (*command)[read_bytes - 1] = '\0';
    }
}

void execute_command(char *command) {
    char *args[MAX_ARGS];
    size_t arg_count = 0;
    pid_t pid;

    /* Tokenize the command */
    char *token = strtok(command, " ");
    while (token != NULL && arg_count < MAX_ARGS - 1) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL; /* Null-terminate the argument list */

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        execve(args[0], args, environ);
    } else {
        /* Parent process */
        wait(NULL);  /* Wait for the child to finish */
    }
}

int main(void) {
    char *command = NULL;

    while (1) {
        read_command(&command);

        /* Check for exit command */
        if (strcmp(command, "exit") == 0) {
            free(command);
        }

        execute_command(command);
    }

    return 0;
}

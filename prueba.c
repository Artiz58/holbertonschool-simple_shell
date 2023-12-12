#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARG_SIZE 64

void display_prompt() {
    printf("($) ");
    fflush(stdout);
}

void execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        /*  Child process */
        char *args[MAX_ARG_SIZE];
        char *token = strtok(command, " ");
        int i = 0;

        while (token != NULL && i < MAX_ARG_SIZE - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;  /*  Null-terminate the argument list */

        if (execvp(args[0], args) == -1) {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("Error");
    } else {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char *input = NULL;  /* Line buffer */
    size_t len = 0;      /* Initial size of the buffer */
	ssize_t read;

    while (1) {
        display_prompt();

        read = getline(&input, &len, stdin);

        if (read == -1) {
            /* Handle end-of-file condition (Ctrl+D) */
            printf("\n");
            break;
        }

        if (input[read - 1] == '\n') {
            /* Remove the newline character */
            input[read - 1] = '\0';
        }

        if (strlen(input) > 0) {
            execute_command(input);
        }
    }

    free(input);  /* Release dynamically allocated memory */

    return 0;
}

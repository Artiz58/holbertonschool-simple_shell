#include "shell.h"

#define MAX_INPUT_SIZE 1024

void display_prompt() {
    printf("#cisfun$ ");
    fflush(stdout);
}

void execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        char **args = malloc(2 * sizeof(char *));
        if (args == NULL) {
            perror("Error");
            exit(EXIT_FAILURE);
        }

        args[0] = command;
        args[1] = NULL;

        if (execve(command, args, NULL) == -1) {
            perror("Error");
            free(args);
            exit(EXIT_FAILURE);
        }

        free(args);
    } else if (pid < 0) {
        perror("Error");
    } else {
        waitpid(pid, &status, 0);
    }
}

int main(void) {
    char input[MAX_INPUT_SIZE];

    while (1) {
        display_prompt();

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        execute_command(input);
    }

    return EXIT_SUCCESS;
}

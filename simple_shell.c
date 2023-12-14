#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute(char *input) {
    pid_t pid = fork();
    int status;

    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        /* Child process */
        char *argv[] = {"/bin/sh", "-c", NULL, NULL};

        /* Allocate memory for the command string */
        argv[2] = malloc(strlen(input) + 1);
        if (argv[2] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }

        /* Copy the input string into the allocated memory */
        strcpy(argv[2], input);

        execvp(argv[0], argv);

        /* If execvp fails, perror and exit */
        perror("Exec failed");
        exit(1);
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input[1024];

    while (1) {
        printf("# ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("\n");
            break;
        }
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }
        execute(input);
    }
    return 0;
}

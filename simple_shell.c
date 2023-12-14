#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void display_prompt(void) {
    printf("#cisfun$ ");
    fflush(stdout);
}

int main(void) {
    char *buffer = NULL;
	size_t bufsize = 0;
    char *args[2];
    ssize_t read_chars;
    pid_t child_pid;
    int status;

    while (1) {
        display_prompt();

        /* Read a line from the user using getline */
        read_chars = getline(&buffer, &bufsize, stdin);

        if (read_chars == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        if (read_chars == 1) {
            /* Empty line, ignore */
            continue;
        }

        /* Null-terminate the string */
        buffer[read_chars - 1] = '\0';

        /* Fork a child process */
        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            /* Child process */

            /* Parse the command */
            args[0] = buffer;
            args[1] = NULL;

            /* Execute the command */
            execve(buffer, args, NULL);

            /* If execve fails */
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            /* Parent process */

            /* Wait for the child to complete */
            waitpid(child_pid, &status, 0);

            /* Check if the executable was not found */
            if (WIFEXITED(status) && WEXITSTATUS(status) == 127) {
                fprintf(stderr, "%s: command not found\n", buffer);
            }
        }
    }
    free(buffer);

    return (EXIT_SUCCESS);
}

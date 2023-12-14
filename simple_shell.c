#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/* Use a separate function to avoid code duplication */
void display_prompt(void) {
  printf("($) ");
  fflush(stdout);
}

int main(void) {
  char *buffer = NULL;
  size_t bufsize = 0;
  char *args[BUFFER_SIZE]; /* Array size should be large enough */
  ssize_t read_chars;
  pid_t child_pid;
  int status;
  int arg_count = 0;
  char *token;

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

    /* Parse the command */
    token = strtok(buffer, " ");

    while (token != NULL) {
      args[arg_count] = token;
      arg_count++;
      token = strtok(NULL, " ");
    }
    args[arg_count] = NULL; /* Terminate arguments array */

    /* Fork a child process */
    child_pid = fork();

    if (child_pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
      /* Child process */
      execve(args[0], args, NULL); /* Use the correct arguments array */
      perror("execve"); /* Report error on failure */
      exit(EXIT_FAILURE);
    } else {
      /* Parent process */
      waitpid(child_pid, &status, 0); /* Wait for child completion */

      /* Check if the executable was not found */
      if (WIFEXITED(status) && WEXITSTATUS(status) == 127) {
        fprintf(stderr, "%s: command not found\n", args[0]);
      }
    }
  }

  free(buffer); /* Free allocated memory */

  return EXIT_SUCCESS;
}

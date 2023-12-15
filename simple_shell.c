#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

extern char **environ;

int main(void) {
  char buffer[BUFFER_SIZE];
  char *command;
  char *args[BUFFER_SIZE];
  int i = 0;
  char *path_entry;

  while (1) {
    /* Print the prompt */
    printf("($) ");
    fflush(stdout);

    /* Read the command */
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
      /* Handle end of file (Ctrl+D) */
      printf("\nExiting...\n");
      break;
    }

    /* Extract the command and remove the newline character */
    command = strtok(buffer, "\n");

    /* Check for empty command */
    if (*command == '\0') {
      continue;
    }

    /* Tokenize the command and populate the args array */
    args[i++] = strtok(command, " ");
    while ((args[i++] = strtok(NULL, " ")) != NULL);

    /* Search for the command in the PATH */
    for (path_entry = environ[0]; path_entry != NULL; path_entry = path_entry + strlen(path_entry) + 1) {
      /* Build the full path */
      char *full_path = malloc(strlen(path_entry) + strlen(args[0]) + 2);
      strcpy(full_path, path_entry);
      strcat(full_path, "/");
      strcat(full_path, args[0]);

      /* Check if the file exists and is executable */
      if (access(full_path, X_OK) == 0) {
        /* Execute the command */
        if (fork() == 0) {
          execve(full_path, args, environ);
          perror("Error");
          exit(EXIT_FAILURE);
        } else {
          wait(NULL);
          break;
        }
      }
      free(full_path);
    }

    /* The command was not found */
    if (path_entry == NULL) {
      printf("Command not found: %s\n", args[0]);
    }
  }

  return 0;
}

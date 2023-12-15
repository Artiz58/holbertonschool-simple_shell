#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256
#define NUM_PATH_ENTRIES 5

extern char **environ;

int main(void) {
  char buffer[BUFFER_SIZE];
  char *command;
  char *args[BUFFER_SIZE];
  int i = 0;
  int j;
  int command_found = 0;
  char *full_path;
  char *path_entries[NUM_PATH_ENTRIES] = {
    "/usr/local/bin/",
    "/usr/bin/",
    "/bin/",
    "/usr/local/games/",
    "/usr/games/"
  };

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

    /* Set the command to "/bin/ls" */
    command = "/bin/ls";

    /* Tokenize the command and populate the args array */
    args[0] = strtok(command, " ");
    i = 1;
    while ((args[i++] = strtok(NULL, " ")) != NULL && i < BUFFER_SIZE - 1);

    /* Search for the command in the specified path entries */
    for (j = 0; j < NUM_PATH_ENTRIES; ++j) {
      /* Build the full path */
      full_path = malloc(strlen(path_entries[j]) + strlen(args[0]) + 2);
      if (full_path == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
      }
      strcpy(full_path, path_entries[j]);
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
          command_found = 1;
          break;
        }
      }
      free(full_path);
    }

    /* The command was not found in the specified paths */
    if (!command_found) {
      printf("Command not found: %s\n", args[0]);
    }
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 128

void prompt() {
  printf("($) ");
}

extern char **environ; // Declare the external variable

int main() {
  char buffer[BUFFER_SIZE];
  char *command;

  while (1) {
    prompt();

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
      printf("\n");
      break;
    }

    command = strtok(buffer, " \n");

    if (!command || strlen(command) == 0) {
      continue;
    }

    if (execve(command, NULL, environ) == -1) { // Use environ instead of envp
      printf("'%s': No such file or directory\n", command);
    }
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void prompt() {
  printf("#cisfun$ ");
}

extern char **environ;

int main() {
  char line[BUFFER_SIZE];
  char *args[2];
  int status;
  pid_t pid;

  args[0] = line;
  args[1] = NULL;

  while (1) {
    prompt();

    /* Read the command line */
    if (fgets(line, BUFFER_SIZE, stdin) == NULL) {
      /* Handle Ctrl+D */
      if (feof(stdin)) {
        printf("\n");
        break;
      } else {
        perror("fgets");
        exit(1);
      }
    }

    /* Remove trailing newline character */
    line[strcspn(line, "\n")] = '\0';

    /* Check for empty command */
    if (strlen(line) == 0) {
      continue;
    }

    /* Check for built-in command (currently only "exit") */
    if (strcmp(line, "exit") == 0) {
      break;
    }

    /* Fork a child process */
    pid = fork();

    if (pid == -1) {
      perror("fork");
      exit(1);
    }

    if (pid == 0) {
      /* Child process */
      execve(line, args, environ);
      perror("execve");
      exit(1);
    } else {
      /* Parent process */
      waitpid(pid, &status, 0);
    }
  }

  return 0;
}

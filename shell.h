#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_LINE_LENGTH 256
#define MAX_ARGS 100

void execute_command(char *full_path, char *args[]);

#endif

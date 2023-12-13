#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void execute_command(char **args);
void check_command(char *command);
void parse_and_execute(char *input);

#endif

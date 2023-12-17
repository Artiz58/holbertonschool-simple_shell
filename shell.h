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
#define MAX_PATHS 5
/* simple_fun.c */
void sigintHandler();
void display_prompt(void);
ssize_t get_command(char **buffer, size_t *size);
/* check_fun.c */
int check_access(char *command, char *args[], char *path[]);
/* exec_fun.c */
void execute_command(char *full_path, char *args[]);
/* parse_fun.h */
int parse_command(char *command, char *args[]);

#endif

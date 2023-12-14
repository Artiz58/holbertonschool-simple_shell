#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;
/* simple_shell.c  */
void error(char **args, char *str_line);
int main(void);
/* more_fun.c */
int white_spaces(char **args, char *str_line);
void free_array(char **args);
void remove_newline(char **str_line, ssize_t *read_bytes);
/* funct.c  */
char **get_tokens(char *str_line);
void get_path(char **args, char **environ);
void my_exe(char **args, char **environ);

#endif

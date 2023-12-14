#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* simple_shell.c */
void error(char **args);
void display_prompt(void);
void process_input(char *str_line, size_t len, int *on);
int main(void);
/* more_fun.c */
int white_spaces(char **args, char *str_line);
void free_tokens(char **args);
void remove_newline(char *str_line, ssize_t *read_bytes);
/* funct.c */
char **env_path(char **environ);
char **get_tokens(char *str_line);
void get_path(char **args, char **environ);
void my_exe(char **args, char **environ);
void free_array(char **arr);

#endif

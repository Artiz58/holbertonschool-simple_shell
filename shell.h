#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;
char **env_path(char **environ);
char **get_tokens(char *str_line);
void my_exe(char **args, char **environ);
void remove_newline(char **str_line, ssize_t *read_bytes);
void get_path(char **full_path, char **environ);
void free_array(char **args);
int white_spaces(char **args, char *str_line);
int main(void);

#endif

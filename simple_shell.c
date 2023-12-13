#include "shell.h"

int main(void)
{
    size_t buf_size = 0;
    ssize_t read_bytes;
    char *buf = NULL;
    char *token;
    int status, i = 0, j;
    char **array;

    pid_t child_pid;

    while (1)
    {
        printf("($) ");
        read_bytes = getline(&buf, &buf_size, stdin);

        if (read_bytes == -1)
        {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        if (buf[read_bytes - 1] == '\n')
            buf[read_bytes - 1] = '\0';

        token = strtok(buf, " \t\n");
        array = malloc(sizeof(char *) * 1024);

        while (token)
        {
            array[i] = strdup(token);
            token = strtok(NULL, " \t\n");
            i++;
        }
        array[i] = NULL;

        child_pid = fork();

        if (child_pid == -1)
        {
            perror("Error forking");
            exit(EXIT_FAILURE);
        }
        else if (child_pid == 0)
        {
            if (execvp(array[0], array) == -1)
            {
                perror("Error executing command");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(child_pid, &status, 0);
        }

        for (j = 0; j < i; j++)
            free(array[j]);

        free(array);

        i = 0;
    }
    free(buf);

    return 0;
}


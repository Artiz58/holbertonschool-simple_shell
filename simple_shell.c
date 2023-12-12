#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char *line = NULL; /*buffer*/
	size_t len = 0;  /* Tamaño inicial del buffer */
	
	pid_t pid;
	
	printf("($) ");

	while (1)
	{
    /* Leer el comando del usuario usando getline */
	if (getline(&line, &len, stdin) == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}

        /* Eliminar el carácter de nueva línea del final del comando */
		line[strcspn(line, "\n")] = '\0';

        /* Crear un nuevo proceso */
		pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

    /* Si el proceso es el hijo, ejecutar el comando */
	if (pid == 0)
	{
		execlp(line, line, NULL);

    /* Si execlp falla, imprimir un error */
		perror("Error 404");
		exit(EXIT_FAILURE);
	}

    /* Si el proceso es el padre, esperar a que el hijo termine */
	if (wait(NULL) == -1)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
	}

    /* Liberar la memoria asignada para el comando */
	free(line);

	return (0);
}

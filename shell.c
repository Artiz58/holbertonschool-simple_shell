#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main(void) {
    char input[MAX_INPUT_SIZE];
    char *token;

    while (1) {
        // Mostrar el prompt
        printf("#cisfun$ ");
        
        // Leer la entrada del usuario
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("Error al leer la entrada");
            exit(EXIT_FAILURE);
        }

        // Eliminar el carácter de nueva línea del final de la entrada
        input[strcspn(input, "\n")] = '\0';

        // Dividir la entrada en tokens usando el espacio como delimitador
        token = strtok(input, " ");

        if (token == NULL) {
            // Si no hay comandos, continuar con la siguiente iteración
            continue;
        }

        // Crear un proceso hijo
        pid_t pid = fork();

        if (pid == -1) {
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Este es el código del proceso hijo

            // Ejecutar el comando con su ruta completa
            if (execv(token, &token) == -1) {
                perror("Error al ejecutar el comando");
                exit(EXIT_FAILURE);
            }
        } else {
            // Este es el código del proceso padre

            // Esperar a que el proceso hijo termine
            wait(NULL);
        }
    }

    return 0;
}

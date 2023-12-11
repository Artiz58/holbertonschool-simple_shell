#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    // Crear 5 procesos hijos
    for (int i = 0; i < 5; i++) {
        pid_t child_pid = fork();

        // Manejar errores en fork
        if (child_pid == -1) {
            perror("Error creating child process");
            return 1;
        }

        // Código específico para el proceso hijo
        if (child_pid == 0) {
            char *command[] = {"/bin/ls", "-l", "/tmp", NULL};

            // Ejecutar el comando ls -l /tmp en el proceso hijo
            if (execve(command[0], command, NULL) == -1) {
                perror("Error executing command");
                return 1;
            }
        }

        // Esperar a que el proceso hijo termine antes de crear uno nuevo
        wait(NULL);
    }

    return 0;
}

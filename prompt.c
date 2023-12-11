#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *line = NULL;
	size_t len = 0;

	printf("($) ");

	ssize_t read = getline(&line, &len, stdin);

	if (read == -1)
	{
		printf("Error al leer la linea.\n");
		free(line);
		exit(EXIT_FAILURE);
	}

	printf("%s", line);

	free(line);

	return (0);
}

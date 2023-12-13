#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _strtok(const char *str, char delimeter)
{
	int len = strlen(str);
	char *word = (char *)malloc(len + 1);
	int i, j;

	if (word == NULL)
	{
		fprintf(stderr, "Error: Unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0, j = 0; i <= len; i++)
	{
		if (str[i] == delimeter || str[i] == '\0')
		{
			word[j] = '\0';
			if (j > 0)
			{
				printf("%s\n", word);
				j = 0;
			}
		}
		else
		{
			word[j++] = str[i];
		}
	}
	free(word);
}

int main()
{
	const char *inputString = "Hola,Mundo,Programacion,C";
	char delimiter = ',';

	_strtok(inputString, delimiter);

	return (0);
}

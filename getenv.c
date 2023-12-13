#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *homevalue = getenv("HOME");

	printf("%s\n", homevalue);
}

#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;
	pid_t pid;

	printf("Before fork\n");
	pid = fork();
	if (pid == -1)
	{
		perror("Error:\n\n");
		return (1);
	}
	printf("After fork\n");
	my_pid = getpid();
	printf("My pid is %u\n\n", my_pid);

	return (0);
}
int fork2(void)
{
	pid_t father_pid;
	pid_t child_pid;
	child_pid = fork();

	if (child_pid == -1)
	{
        perror("Error:");
        return (1);
    }
    father_pid = getpid();
    printf("Father pid is %u\n", father_pid);
    if (child_pid == 0)
    {
        printf("(%u) Nooooooooo!\n", father_pid);
    }
    else
    {
        printf("(%u) %u, I am your father\n", father_pid, child_pid);
    }

    return (0);
}

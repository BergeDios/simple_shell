#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	pid_t id, id2;

	id = getppid();
	id2 = getpid();

	printf("parent id is: %d\n current proccess id is: %d\n", id, id2);
	return (0);
}

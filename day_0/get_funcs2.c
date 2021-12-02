#include "shell.h"
/**
 * free_strlist - frees a char *list[]
 * @list: list to free
 * Return: 0 on success or -1 on failure
 */
int free_strlist(char *list[])
{
	int pos;

	if (!list)
		return (-1);
	for (pos = 0; list[pos]; pos++)
		free(list[pos]);
	return (0);
}

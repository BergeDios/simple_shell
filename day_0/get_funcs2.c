#include "shell.h"
/**
 * free_strlist - frees a char *list[]
 * @list: list to free
 * Return: 0 on success or -1 on failure
 */
int free_strlist(char *list[])
{
	int pos;

	if (!*list)
		return (-1);
	for (pos = 0; list[pos]; pos++)
		free(list[pos]);
	return (0);
}
/**
 * strtok_save - String to token with save pointer
 * @str: String to evaluate
 * @delim: Array of delimitators
 * @save_ptr: Pointer who saves the next word
 * Return: string token
 */
char *strtok_save(char *str, const char *delim, char **save_ptr)
{
	char *next;

	if (str == NULL)
		str = *save_ptr;
	if (*str == '\0')
	{
		*save_ptr = str;
		return (NULL);
	}

	if (*str == '\0')
	{
		*save_ptr = str;
		return (NULL);
	}

	/*moves next pointer to next delim*/
	next = str + _strcspn(str, delim);

	if (*next == '\0')
	{
		*save_ptr = next;
		return (str);
	}

	*next = '\0';
	*save_ptr = next + 1;
	return (str);
}

/**
 * _strtok - String to token
 * @str: String to evaluate
 * @delim: Array of delimitators
 * Return: A token
 */
char *_strtok(char *str, const char *delim)
{
	static char *oldstr;

	return (strtok_save(str, delim, &oldstr));
}

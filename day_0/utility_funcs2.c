#include "shell.h"

/**
 * _strcspn - count characters until the first
 * occurrence of reject char happens
 *
 * @s: string to be scanned
 * @reject: list of chars to be rejected
 *
 * Return: number of chars counted before the
 * first occurrence of reject
 */
ssize_t _strcspn(const char *s, const char *reject)
{
	unsigned int i = 0;
	unsigned int j = 0;
	ssize_t count = 0;

	while (s[i] != '\0')
	{
		while (reject[j] != '\0')
		{
			if (s[i] == reject[j])
				return (count);
			j++;
		}
		j = 0;
		count++;
		i++;
	}

	return (count);
}
/**
 * ctrl_c - makes ctrl_c print prompt instead of exit
 * @n: num from signal
 * Return: void
 */
void ctrl_c(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n> ", 3);
}

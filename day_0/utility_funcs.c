#include "shell.h"

/**
 * _strcat - concatenate two strings
 * @dest: string to add to
 * @src: string to be added
 * Return: concatenated string
 */

char *_strcat(char *dest, char *src)
{
	int p1 = 0;
	int p2 = 0;

	while (dest[p1] != '\0')
		p1++;

	while (src[p2] != '\0')
	{
		dest[p1 + p2] = src[p2];
		p2++;
	}
	dest[p1 + p2] = '\0';

	return (dest);
}
/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte, to the
 * buffer pointed to by dest.
 * @dest: destination.
 * @src: source.
 * Return: the pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int count = 0;

	while (count >= 0)
	{
		*(dest + count) = *(src + count);
		if (*(src + count) == '\0')
			break;
		count++;
	}
	return (dest);
}
/**
 * _strlen - returns the length of a string
 *@s : input string
 *Return: string length
 */

int _strlen(char *s)
{
	int j = 0;

	while (s[j] != 0)
	{
		j++;
	}
	return (j);
}
/**
 * _strcmp - compares two strings
 * @s1: first string.
 * @s2: second string.
 * @n: number of bytes to compare
 * Return: 0 if s1 and s2 are equals,
 * another number if not.
 */

int _strncmp(char *s1, char *s2, size_t n)
{
	int i = 0, op = 0;

	while (op == 0)
	{
		if (((*(s1 + i) == '\0') && (*(s2 + i)) == '\0') || i == n)
			break;
		op = *(s1 + i) - *(s2 + i);
		i++;
	}

	return (op);
}

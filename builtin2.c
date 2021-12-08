#include "shell.h"
/**
 * find_env - find given environmental variable in linked list
 * @envp: environmental variable linked list
 * @name: new var name
 * Return: idx of node in linked list
 */
int find_env(char *envp[], char *name)
{
	int i = 0;

	while (envp[i])
	{
		if (_strncmp(envp[i], name, (_strlen(name))) == 0)
			break;
		i++;
	}
	return (i);
}
/**
 * _cd - change directory based on the given path
 * @token_list: next working directory
 * Return: 0 on succes -1 on failure
 */
int _cd(char *token_list[])
{
	if (token_list[2])
	{
		perror("Too  many arguments");
		return (-1);
	}
	if (chdir(token_list[1]) == 0)
		return (0);

	perror("Can't access directory");
	return (-1);
}
/**
 * _help - prints help for built in commands
 * @token_list: to grab argument 1
 * Return: 0 on success
 */
int _help(char *token_list[])
{
	if (!token_list[1])
	{
		errno = EINVAL;
		perror("help without arguments");
		return (-1);
	}
	else if (_strcmp(token_list[1], "cd") == 0)
	{
		write(1, "cd [dir] , changes directories\n", 31);
		return (0);
	}
	else if (_strcmp(token_list[1], "env") == 0)
	{
		write(1, "env: prints enviromental variables\n", 36);
		return (0);
	}
	else if (_strcmp(token_list[1], "history") == 0)
	{
		write(1, "history keeps a log of typed commands\n", 39);
		return (0);
	}
	else if (_strcmp(token_list[1], "exit") == 0)
	{
		write(1, "Cleans allocated and exits the shell\n", 38);
		return (0);
	}
	else if (_strcmp(token_list[1], "setenv") == 0)
	{
		write(1, "setenv NAME value\n", 19);
		write(1, "sets new or updates env variables\n", 35);
		return (0);
	}
	else
		perror(token_list[1]);
	return (-1);
}



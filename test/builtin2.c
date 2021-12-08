#include "shell.h"
/**
 * _setenv - creates a new env variables or overwites an existing one
 * @name: name or token_list[1]
 * @value: value or token_lsit [2]
 * @envp: list of env variables
 * Return: 0 on success -1 otherwise
 */
int _setenv(char *name, char *value, char *envp[])
{
	int index = 0, pos_new = 0, pos_env = 0;
	char *concat, **new_envp;

	concat = NULL, new_envp = NULL;
	if (!value)
	{
		perror("Too few arguments\n");
		return (-1);
	}

	concat = malloc((_strlen(name) + _strlen(value) + 2));
	if (concat == NULL)
		return (-1);
	_strcpy(concat, name);
	_strcat(concat, "=");
	_strcat(concat, value);
	printf("concat: %s\n", concat);
	index = find_env(envp, name);
	for (pos_env = 0; envp[pos_env]; pos_env++)
		;
	if (index == pos_env)/*no match path then add new at the end*/
	{
		pos_env++;
		new_envp = malloc(sizeof(char *) * pos_env);
		if (new_envp == NULL)
		{
			free(concat);
			return (-1);
		}
		for (pos_new = 0; envp[pos_new]; pos_new++)
		{
			new_envp[pos_new] = malloc(sizeof(char) * _strlen(envp[pos_new]) + 1);
			if (new_envp[pos_new] == NULL)
			{
				free(concat);
				free_strlist(new_envp);
				free(new_envp);
				return (-1);
			}
			_strcpy(new_envp[pos_new], envp[pos_new]);
		}

		new_envp[pos_new] = malloc(sizeof(char) * _strlen(concat) + 1);
		if (new_envp[pos_new] == NULL)
		{
			free(concat);
			free_strlist(new_envp);
			free(new_envp);
			return (-1);
		}
		_strcpy(new_envp[pos_new], concat);
		pos_new++;
	}
	else/*there was a match, its an overwrite*/
	{
		new_envp = malloc(sizeof(char *) * pos_env);
		if (new_envp == NULL)
		{
			free(concat);
			return (-1);
		}
		for (pos_new = 0; envp[pos_new]; pos_new++)
		{
			if (pos_new == index)
			{
				new_envp[pos_new] = malloc(sizeof(char) * _strlen(concat) + 1);
				if (new_envp[pos_new] == NULL)
				{
					free(concat);
					free(new_envp);
					return (-1);
				}
				_strcpy(new_envp[pos_new], concat);
				continue;
			}
			new_envp[pos_new] = malloc(sizeof(char) * _strlen(envp[pos_new]));
			if (new_envp[pos_new] == NULL)
			{
				free(concat);
				free_strlist(new_envp);
				free(new_envp);
				return (-1);
			}
			_strcpy(new_envp[pos_new], envp[pos_new]);
		}
	}
	envp = malloc(sizeof(char *) * pos_env);
	if (!envp)
	{
		free_strlist(new_envp);
		free(concat);
		free(new_envp);
		return (-1);
	}
	for (pos_new = 0; new_envp[pos_new]; pos_new++)
	{
		envp[pos_new] = malloc(sizeof(char) * _strlen(new_envp[pos_new]) + 1);
		_strcpy(envp[pos_new], new_envp[pos_new]);
	}
	free_strlist(new_envp);
	free(concat);
	free(new_envp);
	return (0);
}
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
	else
	{
		perror("Can't access directory");
		return (-1);
	}
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



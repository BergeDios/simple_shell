#include "shell.h"

/**
 * __exit - exit the functions when "exit" is inputed
 * @line: input to be freed
 * Return: 0 on success
 */
void __exit(char *line)
{
	free(line);
	printf("exiting\n");
	/*
	if (!n)
		exit(0);
	else
		exit(n);
		*/
	exit(0);
}
/**
 * _env - prints currenct enviroment
 * @envp: array of env variables
 * Return: 0 on success
 */
int _env(char *envp[])
{
	int i = 0;

	for (; envp[i]; i++)
	{
		printf("%s\n", envp[i]);
	}
	return (0);
}
/**
 * _setenv - creates a new env variables or overwites an existing one
 * @line: inputed line
 * @envp: list of env variables
 * Return: 0 on success -1 otherwise
 */

int _setenv(char *newvar, char *envp[])
{
	int index = 0, pos_new = 0, pos_env = 0;
	char *name, *env_var_copy, **new_envp;

	if (newvar == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		return (-1);
	}
	name = strtok(newvar, "=");
	env_var_copy = malloc(sizeof(char) * (_strlen(newvar)));
	if (env_var_copy == NULL)
		return (-1);
	_strcpy(env_var_copy, newvar);
	index = find_env(envp, name);
	printf("**FIRST SET OF ENV**\n");
	for (pos_env = 0; envp[pos_env]; pos_env++)
	{
		printf("%s\n", envp[pos_env]);
	}
	if (index == pos_env)/*no match path then add new at the end*/
	{
		pos_env++;
		new_envp = malloc(sizeof(char *) * pos_env);
		if (!new_envp)
			return (-1);
		for (pos_new = 0; envp[pos_new]; pos_new++)
		{
			new_envp[pos_new] = envp[pos_new];
		}
		new_envp[pos_new] = newvar;
		pos_new++;
		new_envp[pos_new] = NULL;
	}
	else/*there was a match, its an overwrite*/
	{
		new_envp = malloc(sizeof(char *) * pos_env);
		if (new_envp == NULL)
			return (-1);
		for (pos_new = 0; envp[pos_new]; pos_new++)
		{
			if (pos_new == index)
			{
				new_envp[pos_new] = newvar;
				continue;
			}
			new_envp[pos_new] = envp[pos_new];
		}
		pos_new++;
		new_envp[pos_new] = NULL;
	}
	pos_new = 0;
	printf("**AFTER SETENV**\n");
	for (pos_new = 0; new_envp[pos_new]; pos_new++)
	{
		printf("%s\n", new_envp[pos_new]);
	}
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
	char *token;

	while (envp[i])
	{
		token = strtok(envp[i], "=");
		if (_strcmp(token, name) == 0) /* if matches entirely, break return i*/
			break;
		i++;
	}
	return (i);
}

/**
 * built_in - checks if command call is to a built in function
 * @token_list: to bring token_list[0]
 * @envp: array of pointers to env variables
 * Return: 0 succes or -1
 */
int built_in(char *token_list[], char *envp[], char *line)
{
	int i = -1;
	int l = (_strlen(token_list[0]));

	(void)envp;
	if (_strncmp(token_list[0], "exit", 4) == 0)
	{
		__exit(line);
		i = 1;
	}
	/*else if (_strncmp(token_list[0], "cd", l) == 0)
	{
		_cd(char *dest, char *src);
		i = 0;
	}*/
	else if (_strncmp(token_list[0], "env", l) == 0)
	{
		_env(envp);
		i = 0;
	}
	else if (_strncmp(token_list[0], "setenv", l) == 0)
	{
		_setenv(token_list[1], envp);
		i = 0;
	}
	/*else if (_strncmp(line, "unsetenv", l) == 0)
	{
		_unsetenv(envp);
		i = 0;
	}*/
	return (i);
}

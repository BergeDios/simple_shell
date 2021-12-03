#include "shell.h"
#include <errno.h>

/**
 * __exit - exit the functions when "exit" is inputed
 * @line: input to be freed
 * @token_list: array env
 * @envp_copy: lo deice el nombre
 * Return: 0 on success
 */
void __exit(int n, char *line, char *token_list[], char *envp_copy[])
{

	if (line)
		free(line);
	/*here is the braking point*/
	if (token_list)
		free_strlist(token_list);
	if (envp_copy)
		free_strlist(envp_copy);
	printf("exiting\n");

	if (n)
		exit(n);
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
 * @name: name or token_list[1]
 * @value: value or token_lsit [2]
 * @envp: list of env variables
 * Return: 0 on success -1 otherwise
 */

int _setenv(char *name, char *value, char *envp[])
{
	int index = 0, pos_new = 0, pos_env = 0;
	char *concat, **new_envp;

	concat = NULL;
	if (!value)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		return (-1);
	}

	concat = malloc((_strlen(name) + _strlen(value) + 1));
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
		printf("no match path\n");
		pos_env++;
		printf("going for malloc\n");
		new_envp = malloc(sizeof(char *) * pos_env);
		if (new_envp == NULL)
		{
			printf("going to free concat\n");
			free(concat);
			return (-1);
		}
		printf("did the malloc\n");
		for (pos_new = 0; envp[pos_new]; pos_new++)
		{
			printf("going to copy %d\n", pos_new);
			new_envp[pos_new] = malloc(sizeof(char) * _strlen(envp[pos_new]));
			if (new_envp[pos_new] == NULL)
			{
				free(concat);
				free_strlist(new_envp);
			}
			_strcpy(new_envp[pos_new], envp[pos_new]);
		}
		printf("did the for\n");

		new_envp[pos_new] = malloc(sizeof(char) * _strlen(concat));
		printf("doing the malloc\n");
		if (new_envp[pos_new] == NULL)
		{
			free(concat);
			free_strlist(new_envp);
		}
		printf("going to copy hu go\n");
		_strcpy(new_envp[pos_new], concat);
		printf("copied hu go\n");
		pos_new++;
		/*new_envp[pos_new] = NULL;*/
	}
	else/*there was a match, its an overwrite*/
	{
		printf("there was a match\n");
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
				new_envp[pos_new] = malloc(sizeof(char) * _strlen(concat));
				if (new_envp[pos_new] == NULL)
				{
					free(concat);
					free_strlist(new_envp);
				}
				_strcpy(new_envp[pos_new], concat);
				continue;
			}
			new_envp[pos_new] = malloc(sizeof(char) * _strlen(envp[pos_new]));
			if (new_envp[pos_new] == NULL)
			{
				free(concat);
				free_strlist(new_envp);
			}
			_strcpy(new_envp[pos_new], envp[pos_new]);
		}
		new_envp[pos_new] = NULL;
	}
	printf("**AFTER SETENV**\n");
	for (pos_new = 0; new_envp[pos_new]; pos_new++)
	{
		printf("%s\n", new_envp[pos_new]);
	}
	envp = malloc(sizeof(char *) * pos_env);
	if (!envp)
	{
		free_strlist(new_envp);
		free(concat);
		return (-1);
	}
	for (pos_new = 0; new_envp[pos_new]; pos_new++)
	{
		envp[pos_new] = malloc(_strlen(new_envp[pos_new]));
		_strcpy(envp[pos_new], new_envp[pos_new]);
	}
	free_strlist(new_envp);
	free(concat);
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
		if (_strncmp(envp[i], name, (_strlen(name))) == 0) /* if matches entirely, break return i*/
			break;
		i++;
	}
	return (i);
}
/**
 * _cd - change directory based on the given path
 * @path: next working directory
 * Return: 0 on succes -1 on failure
 */
int _cd(char *token_list[])
{
	if (token_list[2])
	{
		printf("To many arguments\n");
		return (-1);
	}
	if (chdir(token_list[1]) == 0)
		return (0);
	else
	{
		printf("errno: %d Can't access %s\n", errno, token_list[1]);
		return (-1);
	}
}


/**
 * built_in - checks if command call is to a built in function
 * @token_list: to bring token_list[0]
 * @envp: array of pointers to env variables
 * @envp_copy: lo dice el nombre
 * Return: 0 succes or -1
 */
int built_in(char *token_list[], char *envp[], char *envp_copy[], char *line)
{
	int i = -1;
	int l = (_strlen(token_list[0]));

	(void)envp;
	if (_strncmp(token_list[0], "exit", 4) == 0)
	{
		__exit(3, line, token_list, envp_copy);
		i = 1;
	}
	else if (_strncmp(token_list[0], "cd", l) == 0)
	{
		_cd(token_list);
		i = 0;
	}
	else if (_strncmp(token_list[0], "env", l) == 0)
	{
		_env(envp);
		i = 0;
	}
	/*else if (_strncmp(token_list[0], "setenv", l) == 0)
	{
		_setenv(token_list[1], token_list[2], envp);
		i = 0;
	}
	*//*else if (_strncmp(line, "unsetenv", l) == 0)
	{
		_unsetenv(envp);
		i = 0;
	}*/
	return (i);
}

#include "shell.h"
/**
 * __exit - exit the functions when "exit" is inputed
 * @line: input to be freed
 * Return: 0 on success
 */
int __exit(char *line)
{
	free(line);
	return (0);
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
 * built_in - checks if command call is to a built in function
 * @token_list: to bring token_list[0]
 * @line: to clean line when needed
 * @envp: array of pointers to env variables
 * Return: 0 succes or -1
 */
int built_in(char *token_list[], char *line, char *envp[])
{
	int i = -1;
	int l = (_strlen(token_list[0]));

	(void)envp;
	if (_strncmp(token_list[0], "exit", l) == 0)
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
	/*else if (_strncmp(token_list[0], "setenv", l) == 0)
	{
		_setenv(envp);
		i = 0;
	}
	else if (_strncmp(token_list[0], "unsetenv", l) == 0)
	{
		_unsetenv(envp);
		i = 0;
	}*/
	return (i);
}

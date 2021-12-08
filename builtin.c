#include "shell.h"
#include <errno.h>

/**
 * history - displays the history list, one command by line, preceded by number
 */
void history(void)
{
	int pos;

	for (pos = 0; history_list[pos]; pos++)
		printf("%d %s", pos, history_list[pos]);
}
/**
 * save_history - writes on the user log the commands that were
 * executed during runtime
 *
 * Return: 0 on success | -1 on failure
 */
int save_history(void)
{
	int pos, log_fd;

	log_fd = open("./log", O_CREAT | O_APPEND | O_RDWR, 0666);
	if (log_fd == -1)
	{
		perror("Couldn't open log file");
		return (-1);
	}
	for (pos = 0; history_list[pos]; pos++)
	{
		write(log_fd, history_list[pos], _strlen(history_list[pos]));
		/*check for error */
	}
	close(log_fd);
	return (0);
}
/**
 * __exit - exit the functions when "exit" is inputed
 * @line: input to be freed
 * @token_list: array env
 * @envp_copy: lo deice el nombre
 * Return: 0 on success
 */
void __exit(char *line, char *token_list[], char *envp_copy[])
{
	int n = 0;

	if (line)
		free(line);
	if (token_list)
		free_strlist(token_list);
	if (envp_copy)
		free_strlist(envp_copy);

	save_history();
	free_strlist(history_list);

	exit(n);
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
		write(1, envp[i], _strlen(envp[i]));
		write(1, "\n", 1);
	}
	return (0);
}
/**
 * built_in - checks if command call is to a built in function
 * @token_list: to bring token_list[0]
 * @envp: array of pointers to env variables
 * @envp_copy: lo dice el nombre
 * @line: input line
 * Return: 0 succes or -1
 */
int built_in(char *token_list[], char *envp[], char *envp_copy[], char *line)
{
	int i = -1;

	(void)envp;
	if (_strncmp(token_list[0], "exit", 4) == 0)
	{
		__exit(line, token_list, envp_copy);
		i = 1;
	}
	else if (_strncmp(token_list[0], "cd", 2) == 0)
	{
		_cd(token_list);
		i = 0;
	}
	else if (_strncmp(token_list[0], "env", 3) == 0)
	{
		if (token_list[1])
		{
			perror("Too many arguments");
			return (-1);
		}
		_env(envp);
		i = 0;
	}
	else if (_strncmp(token_list[0], "help", 4) == 0)
	{
		_help(token_list);
		i = 0;
	}
	else if (_strncmp(token_list[0], "history", 7) == 0)
	{
		history();
		i = 0;
	}
	return (i);
}

#include "shell.h"
#include <errno.h>
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
/**
 * ctrl_d - exits program if ctrl_d pressed
 * @n: num of chars read
 * @line: line inputed by user
 * @token_list: env var
 * @envp_copy: lo dice
 * Return: nothing
 */
void ctrl_d(int n, char *line, char *token_list[], char *envp_copy[])
{
	(void)n;
	__exit(2, line, token_list, envp_copy);
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
}
/**
 * _getcommand - gets the line and separates into tokens
 * @token_list: pointer to token list
 * @line: pointer to prompt input
 * Return: 0 on succes | -1 on failure
 */
int _getcommand(char *token_list[], char *line)
{
	char *token = NULL;
	int pos_tok = 0;

	token = _strtok(line, " ");
	while (token != NULL)
	{
		token_list[pos_tok] = malloc(sizeof(char) * (_strlen(token) + 1));
		_strcpy(token_list[pos_tok], token);
		pos_tok++;
		token = _strtok(NULL, " ");
	}
	token_list[pos_tok] = NULL;
	return (0);
}

/**
 * _getenv - gets path dirs and puts it into array
 * @path_list: array to be stored at
 * @envp_copy: array of enviromental variables
 * Return: 0 if success
 */

int _getenv(char *path_list[], char *envp_copy[])
{

	/* This is currently breaking the envp variable and we cant use it for _env */
	char *token;
	int i = 0, pos_path = 0;
	size_t l = 4;

	token = NULL;
	for (i = 0; envp_copy[i]; i++)
	{
		token = _strtok(envp_copy[i], "=");
		if (_strncmp(token, "PATH", l) == 0)
		{
			token = _strtok(NULL, "=");
			token = _strtok(token, ":");
			while (token != NULL)
			{
				path_list[pos_path] = token;
				pos_path++;
				token = _strtok(NULL, ":");
			}
		}

	}

	if (path_list == NULL)
		return (-1);
	return (0);
}

int _execute_command(char *path, char *token_list[], char *envp[])
{
	int status, exit_stat = 0;
	pid_t id;

	id = fork();
	if (id > 0)
	{
		wait(&status);
		if (status == 0)
		{
		/*free_strlist(token_list);*/
		return (0);
		}
	}
	else if (id == 0)
	{
		exit_stat = execve(path, token_list, envp);
		if (exit_stat == -1)
		{
			perror("execve failed");
			return (-1);
		}
	}
	else
		perror ("fork failed");
	return (-1);
}

/**
 * _findcommand - gets command with path en executes if possible
 * @path_list: array with path options
 * @token_list: pointer to list of tokens
 * @envp: array of env variables
 * Return: 0 on succes or -1
 */
int _findcommand(char *path_list[], char *token_list[], char *envp[])
{
	char path[1024];
	int pos_path = 0, acc;

	acc = 0;

	/* This part handles if the command is passed with an absolute path */
	if (token_list[0][0] == '.' || token_list[0][0] == '/')
	{
		acc = access(token_list[0], (R_OK | X_OK));
		if (acc == 0)
			return (_execute_command(token_list[0], token_list, envp));
	}
	for (pos_path = 0; path_list[pos_path]; pos_path++)
	{
		_strcpy(path, path_list[pos_path]);
		_strcat(path, "/");
		_strcat(path, token_list[0]);
		acc = access(path, (R_OK | X_OK));

		if (acc == 0)
		{
			return (_execute_command(path, token_list, envp));
		}
	}
	perror(path);
	return (-1);
}

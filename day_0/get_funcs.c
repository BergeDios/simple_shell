#include "shell.h"
/**
 * ctrl_c - makes ctrl_c print prompt instead of exit
 * @n: num from signal
 * Return: void
 */
void ctrl_c(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * ctrl_d - exits program if ctrl_d pressed
 * @n: num of chars read
 * @line: line inputed by user
 * Return: nothing
 */
void ctrl_d(int n, char *line)
{
	(void)n;
	free(line);
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

	token = strtok(line, " ");
	while (token != NULL)
	{
		token_list[pos_tok] = token;
		pos_tok++;
		token = strtok(NULL, " ");
	}
	return (0);
}

/**
 * _getenv - gets path dirs and puts it into array
 * @path_list: array to be stored at
 * @envp: array of enviromental variables
 * Return: 0 if success
 */

int _getenv(char *path_list[], char *envp[])
{
	char *token;
	int i = 0, pos_path = 0;
	size_t l = 4;

	token = NULL;
	for (i = 0; envp[i]; i++)
	{
		token = strtok(envp[i], "=");
		if (strncmp(token, "PATH", l) == 0)
		{
			token = strtok(NULL, "=");
			token = strtok(token, ":");
			while (token != NULL)
			{
				path_list[pos_path] = token;
				pos_path++;
				token = strtok(NULL, ":");
			}
		}

	}
	if (path_list == NULL)
		return (-1);
	return (0);
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
	int pos_path = 0, a;
	pid_t id;

	a = 0, id = 0;
	for (pos_path = 0; path_list[pos_path]; pos_path++)
	{
		_strcpy(path, path_list[pos_path]);
		_strcat(path, "/");
		_strcat(path, token_list[0]);
		a = access(path, (R_OK | X_OK));
		if (a == 0)
		{
			/*printf("access granted from pid: %d\n", getpid());*/
			id = fork();
			if (id != 0)
			{
				wait(NULL);
				return (0);
			}
			else
			{
				/*printf("executing from pid: %d\n", getpid());*/
				execve(path, token_list, envp);
			}
		}
	}
	write(STDOUT_FILENO, "Error: Executable file not found\n", 33);
	return (-1);
}

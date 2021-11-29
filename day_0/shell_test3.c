#include "shell.h"
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
		if (_strncmp(token, "PATH", l) == 0)
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
			id = fork();
			if (id != 0)
				wait(0);
			else
			{
				printf("hello from the child process\n");
				execve(path, token_list, envp);
			}
		}
	}
	return (0);
}




int main(int argc, char *argv[], char *envp[])
{
	char *path_list[1024], *token_list[1024], *line;
	size_t n;

	n = 1024;
	(void)argc, (void)argv;
	line = NULL, *token_list = NULL, *path_list = NULL;

	while (1)
	{
		printf("> ");
		if ((getline(&line, &n, stdin)) >= 0)
		{
			line[strlen(line) - 1] = '\0';
			_getcommand(token_list, line);
		}

		_getenv(path_list, envp);

		_findcommand(path_list, token_list, envp);
		free(line);
	}
	return (0);

}

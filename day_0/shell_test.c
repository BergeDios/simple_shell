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


int _findcommand(char *path_list[], char *token_list[], char *envp[])
{
	char path[1024];
	int pos_path = 0, a;
	pid_t id;

	a = 0, id = 0;
	for (pos_path = 0; path_list[pos_path]; pos_path++)
	{
		strcpy(path, path_list[pos_path]);
		strcat(path, "/");
		strcat(path, token_list[0]);
		a = access(path, (R_OK | X_OK));
		if (a == 0)
		{
			printf("access granted from pid: %d\n", getpid());
			id = fork();
			if (id != 0)
			{
				wait(NULL);
				return (0);
			}
			else
			{
				printf("executing from pid: %d\n", getpid());
				execve(path, token_list, envp);
			}
		}
	}
	return (-1);
}




int main(int argc, char *argv[], char *envp[])
{
	char *path_list[1024], *token_list[1024], *line/*, *s_path*/;
	size_t n;
	int i;

	n = 1024;
	(void)argc, (void)argv;
	line = NULL, *token_list = NULL, *path_list = NULL/*, s_path = NULL*/;

	while (1)
	{
		printf("> ");
		if ((getline(&line, &n, stdin)) >= 0)
		{
			line[strlen(line) - 1] = '\0';
			if (strncmp(line, "exit", 4) == 0)
			{
				printf("exiting\n");
				free(line);
				return (0);
			}
			_getcommand(token_list, line);
		}

		_getenv(path_list, envp);

		_findcommand(path_list, token_list, envp);
	
		for (i = 0; token_list[i]; i++)
			token_list[i] = NULL;
	}

/*	
	for (i = 0; token_list[i]; i++)
		free(token_list[i]);
	free(token_list[i]);


	for (i = 0; path_list[i]; i++)
		free(path_list[i]);
	free(path_list[i]);
	free(path_list);
	free(token_list);
*/
	free(line);

	return (0);

}

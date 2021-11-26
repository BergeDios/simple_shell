#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
/**
 * _getcommand - gets the line and separates into tokens
 * @token_list: pointer to token list
 *
 * Return: 0 on succes | -1 on failure
 */
int _getcommand(char *token_list[])
{
	char *token = NULL, *line[1024];
	int pos_tok = 0;
	size_t n;

	n = 1024;
	*line = NULL;
	printf("> ");
	getline(line, &n, stdin);

	token = strtok(*line, " ");
	while (token != NULL)
	{
		printf("t: %s, ", token);
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
	int i = 0, pos_path = 0, l = 0;
	char *token, *tokcopy;

	token = NULL, tokcopy = NULL;
	for (i = 0; envp[i]; i++)
	{
		token = strtok(envp[i], "=");
		l = strlen(token);
		tokcopy = strncpy(tokcopy, token, l);

		if (strcmp(tokcopy, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			token = strtok(token, ":");
			while (token != NULL)
			{
				printf("token is: %s\n", token);
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

int main(int argc, char *argv[], char *envp[])
{
	char *path_list[1024], *token_list[1024], *s_path;
	int pos_path = 0;

	(void)argc, (void)argv;
	*path_list = NULL, *token_list = NULL, s_path = NULL;

	while (1)
	{
		_getcommand(token_list);
		_getenv(path_list, envp);
		for (pos_path = 0; path_list[pos_path]; pos_path++)
			printf("%s\n", path_list[pos_path]);
		for (pos_path = 0; path_list[pos_path]; pos_path++)
		{
			s_path = strcat(path_list[pos_path], "/");
			s_path = strcat(s_path, token_list[0]);
			printf("%s\n", s_path);

		}
	}
	return (0);

}

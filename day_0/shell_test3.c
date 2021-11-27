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
char **_getcommand(char *line2)
{
	char *token = NULL, **token_list;
	int pos_tok = 0;

	printf("line in getcommand is: %s\n", line2);
	token_list = malloc(sizeof(char) * 100);
	token = strtok(line2, " ");
	while (token != NULL)
	{
		printf("token: %s\n", token);
		token_list[pos_tok] = token;
		pos_tok++;
		token = strtok(NULL, " ");
	}
	return (token_list);
}

/**
 * _getenv - gets path dirs and puts it into array
 * @path_list: array to be stored at
 * @envp: array of enviromental variables
 * Return: 0 if success
 */
/*
 * int _getenv(char *path_list[], char *envp[])
{
	int i = 0, pos_path = 0;
	char *token;
	size_t l = 4;

	token = NULL;
	printf("entre a getenv\n");

	for (i = 0; envp[i]; i++)
	{
		token = strtok(envp[i], "=");
		if (strncmp(token, "PATH", l) == 0)
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
}*/

int main(int argc, char *argv[], char *envp[])
{
	char *path_list[1024], **token_list, *line[1024], line2[1024]/*, *s_path*/;
	/*int pos_path = 0;*/
	size_t n;
	int i;

	n = 1024;
	(void)argc, (void)argv, (void)envp;
	*path_list = NULL/*, s_path = NULL*/;

	while (1)
	{
		printf("> ");
		getline(line, &n, stdin);
		printf("line is: %s\n", *line);

		while (*line[i] != '\n')
		{
			printf("%c\n", *line[i]);
			i++;
		}
		printf("line2 is: %s\n", line2);

		token_list = _getcommand(line2);
		for (i = 0; token_list[i]; i++)
			printf("tl[%d]: %s\n", i, token_list[i]);

		/*_getenv(path_list, envp);
		for (pos_path = 0; path_list[pos_path]; pos_path++)
			printf("%s\n", path_list[pos_path]);
		for (pos_path = 0; path_list[pos_path]; pos_path++)
		{
			s_path = strcat(path_list[pos_path], "/");
			s_path = strcat(s_path, token_list[0]);
			printf("%s\n", s_path);

		}*/
	}
	return (0);

}

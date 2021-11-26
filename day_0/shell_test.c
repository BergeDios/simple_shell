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
	char *token, *line[1024];
	int pos_tok = 0;
	size_t n;
	n = 1024;

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
	int i = 0, pos_path = 0;
	char *token;

	for (i = 0; envp[i]; i++)
	{
		token = strtok(envp[i], "=");
		if (strcmp(token, "PATH") == 0)
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
	char *buff[1024], *token, *path_list[1024] = { NULL }, *token_list[1024];
	size_t buffsize;
	int pos_tok = 0, pos_path;
	DIR *dr;
	struct dirent *de;

	buffsize = 1024, *path_list = NULL, *token_list = NULL;
	while (1)
	{
		_getcommand(token_list);
		printf("list of tokens\n");
		for (pos_tok = 0; token_list[pos_tok]; pos_tok++)
			printf("token is: %s\n", token_list[pos_tok]);

		_getenv(path_list, envp);
		for (pos_path = 0; path_list[pos_path]; pos_path++)
		{
			dr = opendir(path_list[pos_path]);
			if (dr == NULL)
				return (-1);
			while ((de = readdir(dr)) != NULL)
				printf("token_list[0]: %s\n", token_list[0]);
				if (strcmp(de->d_name, "ls") == 0)
					printf("encontre: %s\n", de->d_name);
		}
	}
	return (0);

}

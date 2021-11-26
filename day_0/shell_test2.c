#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

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
			printf("token is: %s\n", token);
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
		printf("$ ");
		getline(buff, &buffsize, stdin);

		token = strtok(*buff, " ");
		while (token != NULL)
		{
			token_list[pos_tok] = token;
			pos_tok++;
			token = strtok(NULL, " ");
		}
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
				printf("%s\n", de->d_name);
		}
	}
	return (0);

}

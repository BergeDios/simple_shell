#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
	char *buff[1024], *token, *path_list[1024], *token_list[1024];
	size_t buffsize;
	int pos_tok = 0, pos_env, pos_path;

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
		for (pos_env = 0; envp[pos_env]; pos_env++)
		{
			token = strtok(envp[pos_env], "=");
			if (strcmp(token, "PATH") == 0)
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
		printf("list of path dirs\n");
		for (pos_path = 0; path_list[pos_path]; pos_path++)
			printf("path token is: %s\n", path_list[pos_path]);
	}
	return (0);
}

char *_getenv(char *envp[])
{
	int pos_env, pos_path;
	char *token, *path_list[1024];

	for (pos_env = 0; envp[pos_env]; pos_env++)
	{
		token = strtok(envp[pos_env], "=");
		if (strcmp(token, "PATH") == 0)
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
	return (*path_list);
}

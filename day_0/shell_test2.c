#include "shell.h"
/**
 * main - shell like program
 * @argc: argument counter
 * @argv: argument vector
 * @envp: array of enviromental variables
 * Return: 0 on success
 */

int main(int argc, char *argv[], char *envp[])
{
	char *path_list[1024], *token_list[1024], *line;
	size_t n;
	int i, r, exit_stat/*, pos_free = 0*/;

	n = 1024;
	(void)argc, (void)argv;
	line = NULL, *token_list = NULL, *path_list = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\"(Ô.o)\'> ", 10);
		signal(SIGINT, ctrl_c);/*should make ctrl-c not exit*/
		r = getline(&line, &n, stdin);

		/* first of all we load the envp */
		 _getenv(path_list, envp);

		if (r == -1)
			ctrl_d(r, line);/*makes ctrl d exit"*/
		else
		{
			if (line[0] == '\n')
				continue;
			line[_strlen(line) - 1] = '\0';
			_getcommand(token_list, line);
			exit_stat = built_in(token_list, envp);/* checks if calling built in first */
			if (exit_stat == 1)/* exit */
				return (0);
			else if (exit_stat == -1)/* it didnt find a built in -> searchinv in path_list */
				_findcommand(path_list, token_list, envp);

		}
		printf("\n\nexit_stat: %d\n\nprinting envp\n\n", exit_stat);
		for (i = 0; envp[i]; i++)
			printf("envp[i]: %s\n", envp[i]);
		printf("***********************************\n");
		for (i = 0; token_list[i]; i++)
			token_list[i] = NULL;
	}

	free(line);
	/*if (new_envp)
	{
		for(pos_free = 0; new_envp[pos_free]; pos_free++)
			free(new_envp[pos_free]);
		free(new_envp);
	}*/
	return (0);

}

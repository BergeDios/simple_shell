#include "shell.h"
#include <limits.h>
/**
 * main - shell like program
 * @argc: argument counter
 * @argv: argument vector
 * @envp: array of enviromental variables
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *envp[])
{
	char *path_list[1024], *token_list[1024], *envp_copy[1024];
	char *line, curr_directory[PATH_MAX];
	size_t n;
	int r, builtin_stat, pos_log, pos_cpy;

	n = 1024, pos_log = 0;
	(void)argc, (void)argv;
	line = NULL, *token_list = NULL, *path_list = NULL, *envp_copy = NULL, *history_list = NULL;

	/*copy of envp to tokenize*/
	for (pos_cpy = 0; envp[pos_cpy]; pos_cpy++)
	{
		envp_copy[pos_cpy] = malloc(sizeof(char) * (_strlen(envp[pos_cpy]) + 1));
		_strcpy(envp_copy[pos_cpy], envp[pos_cpy]);
	}
	envp_copy[pos_cpy] = NULL;
	/* first of all we load the envp */
	_getenv(path_list, envp_copy);
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			getcwd(curr_directory, sizeof(curr_directory));
			write(STDOUT_FILENO, curr_directory, _strlen(curr_directory));
			write(STDOUT_FILENO, ": \"(Ô.o)\'> ", 12);
		}
		signal(SIGINT, ctrl_c);/*should make ctrl-c not exit*/
		r = getline(&line, &n, stdin);
/*
		if (r == -1)
			ctrl_d(r, line, token_list, envp_copy);makes ctrl d exit
		else
		{*/

		if (line[0] == '\n')
			continue;

		history_list[pos_log] = malloc(sizeof(char) * _strlen(line) + 1);
		_strcpy(history_list[pos_log], line);
		pos_log++;		
		/*write(log_fd, line, _strlen(line));*/
		line[_strlen(line) - 1] = '\0';
		_getcommand(token_list, line);
		if (r == -1)
			 ctrl_d(r, line, token_list, envp_copy);/*makes ctrl d exit*/
		builtin_stat = built_in(token_list, envp, envp_copy, line);/* checks if calling built in first */
		if (builtin_stat == 0)/* was built in */
			continue;
		else if (builtin_stat == -1)/* it didnt find a built in -> search it in path_list */
			_findcommand(path_list, token_list, envp);
		/*}
		 Checking that envp is not broken
		printf("\n\nexit_stat: %d\n\nprinting envp\n\n", exit_stat);
		for (i = 0; envp[i]; i++)
			printf("envp[i]: %s\n", envp[i]);
		printf("***********************************\n");
		*/
		free_strlist(token_list);
	}
	__exit(0, line, token_list, envp_copy);
	return (0);
}

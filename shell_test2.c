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
	char *path_list[1024], *token_list[1024], *envp_copy[1024], *line;
	size_t n = 1024;
	int r, builtin_stat, pos_log, pos_cpy;

	pos_log = 0, (void)argc, (void)argv, line = NULL, *envp_copy = NULL,
	*token_list = NULL, *path_list = NULL, *history_list = NULL;
	for (pos_cpy = 0; envp[pos_cpy]; pos_cpy++)
	{
		envp_copy[pos_cpy] = malloc(sizeof(char) * (_strlen(envp[pos_cpy]) + 1));
		_strcpy(envp_copy[pos_cpy], envp[pos_cpy]);
	}
	envp_copy[pos_cpy] = NULL;
	_getenv(path_list, envp_copy);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ": \"(Ô.o)\'> ", 12);
		signal(SIGINT, ctrl_c);/*should make ctrl-c not exit*/
		r = getline(&line, &n, stdin);
		if (line[0] == '\n')
			continue;
		history_list[pos_log] = malloc(sizeof(char) * _strlen(line) + 1);
		_strcpy(history_list[pos_log], line), pos_log++;
		line[_strlen(line) - 1] = '\0';
		_getcommand(token_list, line);
		if (r == -1)
			ctrl_d(line, token_list, envp_copy);/*makes ctrl d exit*/
		builtin_stat = built_in(token_list, envp, envp_copy, line);
		if (builtin_stat == 0)/* was built in */
		{
			free_strlist(token_list);
			continue;
		}
		else if (builtin_stat == -1)/* if not a built in -> search it in path_list */
			errstat = _findcommand(path_list, token_list, envp);
		free_strlist(token_list);
	}
	__exit(line, token_list, envp_copy);
	return (0);
}

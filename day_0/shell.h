#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*UTILITY FUNCS*/
char *_strcat(char *dest, char *src);
int _strncmp(char *s1, char *s2, size_t n);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
/*GET FUNCS*/
int _getcommand(char *token_list[], char *line);
int _getenv(char *path_list[], char *envp[]);
int _findcommand(char *path_list[], char *commandyarg[], char *envp[]);
int _execute_command(char *path, char *token_list[], char *envp[]);
void ctrl_c(int n);
void ctrl_d(int n, char *line);

int main(int argc, char *argv[], char *envp[]);

/*BUILT IN FUNCS*/
void __exit(char *line);
int _env(char *envp[]);
int built_in(char *token_list[], char *envp[]);
int find_env(char *envp[], char *name);
int _setenv(char *line, char *envp[]);
	
#endif

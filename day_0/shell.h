#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

/*UTILITY FUNCS*/
char *_strcat(char *dest, char *src);
int _strncmp(char *s1, char *s2, size_t n);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
/*UTILITY FUNCS 2*/
ssize_t _strcspn(const char *s, const char *reject);
/*GET FUNCS*/
int _getcommand(char *token_list[], char *line);
int _getenv(char *path_list[], char *envp_copy[]);
int _findcommand(char *path_list[], char *commandyarg[], char *envp[]);
int _execute_command(char *path, char *token_list[], char *envp[]);
void ctrl_c(int n);
void ctrl_d(int n, char *line, char *token_list[], char *envp_copy[]);
/*GET FUNCS 2*/
int free_strlist(char *list[]);
char *strtok_save(char *str, const char *delim, char **save_ptr);
char *_strtok(char *str, const char *delim);

int main(int argc, char *argv[], char *envp[]);

/*BUILT IN FUNCS*/
void __exit(int n, char *line, char *token_list[], char *envp_copy[]);
int _env(char *envp[]);
int built_in(char *token_list[], char *envp[], char *envp_copy[], char *line);
int find_env(char *envp[], char *name);
int _setenv(char *name, char *value, char *envp[]);

/* GLOBALS TO GO INSIDE STRUCT */
char *history_list[1024];

/* END OF GLOBALS */


#endif

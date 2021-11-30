#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

char *_strcat(char *dest, char *src);
int _strncmp(char *s1, char *s2, size_t n);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _getcommand(char *token_list[], char *line);
int _getenv(char *path_list[], char *envp[]);
int _findcommand(char *path_list[], char *commandyarg[], char *envp[]);
int main(int argc, char *argv[], char *envp[]);
void ctrl_c(int n);
void ctrl_d(int n, char *line);
int __exit(char *line);
int _env(char *envp[]);
int built_in(char *token_list[], char *line, char *envp[]);

#endif

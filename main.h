#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define INPUT_BUFFER_SIZE 1024

extern char **environ;

void _eof(int status, const char *name, char **input);
void _prompt(char *name);
char *_getenv(const char *env);
bool isprintable(char *str);
char *_allocate(const char *name, ssize_t length, char *input);
void _strcpy(char *src, char *dest);
char *get_binary(char *bin_name, char *program_name);
void run_binary(char **binary, char *program_name, char *in_dup, char *input);
void _strcat(char *dest, const char *src);
char *str_dup(const char *buffer);
size_t _strlen(const char *str);
int count_tokens(char *input, const char *delimiter);
int _putchar(int c);
void print_error(char *cause, char *program);
char **tokenize(char *delim, char *copy, char *input, char *program_name);
void free_vectors(char **vectors);
void _puts(char *str);
int _atoi(char *string);
int _strcmp(char *s1, char *s2);
bool is_fully_digits(char *str);
void in_exit(char **args, char *name);
void _env(char **argv, char *name);
void (*get_built_in(char **cmd))(char **argv, char *name);

/**
 * struct built_in - structure of type builtin
 * @funct: function name
 * @fptr: address of function
 */
typedef struct built_in
{
	char *funct;
	void (*fptr)(char **argv, char *prog_name);
} built_t;


#endif /* MAIN_H */

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
#include <fcntl.h>
#include <signal.h>

#define INPUT_BUFFER_SIZE 1024

extern char **environ;

void _eof(int status, const char *name, char **input);
void _prompt(char *name);
char *_getenv(const char *env);
bool isprintable(char *str);
char *_allocate(const char *name, char *input);
void _strcpy(char *dest, char *src);
char *get_binary(char *bin_name, char *program_name);
int run_binary(char **binary, char *program_name, char *input);
void _strcat(char *dest, const char *src);
char *str_dup(const char *buffer);
size_t _strlen(const char *str);
int count_tokens(char *input, const char *delimiter);
int _putchar(int c);
void print_error(char *cause, char *program);
char **tokenize(char *delim, char *input, char *program_name);
void free_vectors(char **vectors);
void _puts(char *str);
int _atoi(char *string);
int _strcmp(char *s1, char *s2);
bool is_fully_digits(char *str);
int in_exit(char **args, char *name);
int _env(char **argv, char *name);
int (*get_built_in(char **cmd))(char **argv, char *name);

/**
 * struct built_in - structure of type builtin
 * @funct: function name
 * @fptr: address of function
 */
typedef struct built_in
{
	char *funct;
	int (*fptr)(char **argv, char *prog_name);
} built_t;

char **dup_env(char **ptr);
ssize_t m_getline(char **lineptr, size_t *n, int fd);
char *m_strtok(char *str, const char *delim);
bool is_delim(char c, const char *delim);
void print_int(int number);
int env_length(char **_environ);
void init_environ(char *name);
int add_env(char *name, char *value);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
int noninteractive(char *program, char *script);
char *read_file(char *program, char *script);
void read_error(ssize_t stat, int file, char *argv, char *name, char *buf);
void create_message(char * message, char *command, char *arg);
int unset_env(char **argv, char *name);
int set_env(char **argv, char *name);
int get_pos(char *env);
int m_cd(char **argv, char *name);
int m_echo(char **argv, int ex_stat);
bool is_echo(char **argv, int exit_stat, int *ex_stat);
void handle_hash(char *command);
bool handle_symbol(char *name, char *input, int *exit_stat);
bool find_symbol(char *input, char *symbol);
int _and(char *name, char *input);
int multiple(char *name, char *input, int flag);
int run_file(char *program, char *file_con);

#endif /* MAIN_H */

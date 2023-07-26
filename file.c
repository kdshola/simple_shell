#include "main.h"

/**
 * read_error - checks for read and write error
 * @stat: file status
 * @file: fd to file to read from
 * @argv: arguement to command
 * @name: program name
 * @buf: pointer to allocated buffer
 * Return: Nothing
 */
void read_error(ssize_t stat, int file, char *argv, char *name, char *buf)
{
	char error[100];

	if (stat == -1)
	{
		create_message(error, "read", argv);
		print_error(error, name);
		free(buf);
		if (file != -1)
			close(file);
		free_vectors(environ);
		exit(-1);
	}
}

/**
 * create_message - creates an error message
 * @message: message pointer
 * @command:  command error
 * @arg: command arguement
 * Return: Nothing
 */
void create_message(char *message, char *command, char *arg)
{
	_strcpy(message, command);
	_strcat(message, ": ");
	_strcat(message, "'");
	_strcat(message, arg);
	_strcat(message, "'");
}

/**
 * read_file - executes shell scripts
 * @program: program name
 * @script: sript name
 * Return: Nothing
 */
char *read_file(char *program, char *script)
{
	int fd = 0;
	size_t size = 1024, total = 0;
	ssize_t let_read = 1024;
	char  error[100], *command = NULL, tmp[1025];

	fd = open(script, O_RDONLY);
	if (fd == -1)
	{
		create_message(error, "open", script);
		print_error(error, program);
		return (NULL);
	}
	command = malloc(sizeof(char) * size);
	if (command == NULL)
		return (NULL);
	command[0] = '\0';
	while (let_read == 1024)
	{
		let_read = read(fd, tmp, 1024);
		read_error(let_read, fd, script, program, command);
		total += let_read;
		if (let_read == 1024)
			command = _realloc(command, size, size + 1024);
		(size += 1024, tmp[let_read] = '\0', _strcat(command, tmp));
	}
	command[total] = '\0';
	if (close(fd) == -1)
	{
		create_message(error, "close", script);
		print_error(error, program);
		return (command);
	}
	return (command);
}
/**
 * noninteractive - executes shell scripts
 * @program: program name
 * @script: sript name
 * Return: 0 on sucess or -1
 */
int noninteractive(char *program, char *script)
{
	int child_hex = 0;
	char *path = NULL, *tmp = NULL, *file_con = NULL;

	path = script;
	if (script[0] != '/' && script[0] != '~' && script[0] != '.')
		tmp = _getenv("PWD");
	path = malloc(_strlen(tmp) + _strlen(script) + 2);
	if (path == NULL)
		return (-1);
	(_strcpy(path, tmp), _strcat(tmp, "/"), _strcat(tmp, script));
	file_con = read_file(program, path);
	if (file_con == NULL)
	{
		if (errno == ENOMEM)
			free_vectors(environ), exit(-1);
		free(path);
		return (-1);
	}
	handle_hash(file_con);
	child_hex = run_file(program, file_con);
	free(path);
	free(file_con);
	return (child_hex);
}

/**
 * run_file - excutes script
 * @program: program name
 * @file_con: file content
 * Return: exit value
 */
int run_file(char *program, char *file_con)
{
	int (*fp)(char **, char *), child_hex = 0;
	char  **token = NULL, *tol = NULL, *tmp = file_con;

	tol = strtok(file_con, "\n");
	while (tol)
	{
		if (handle_symbol(program, tol, &child_hex) == true)
		{
			tol = strtok(NULL, "\n");
			continue;
		}
		token = tokenize(" ", tol, program);
		if (is_echo(token, child_hex, &child_hex) == true)
		{
			tol = strtok(NULL, "\n");
			continue;
		}
		fp = get_built_in(token);
		if (fp)
		{
			child_hex = fp(token, program), free_vectors(token);
			tol = strtok(NULL, "\n");
			continue;
		}
		child_hex = run_binary(token, program, tmp);
		free_vectors(token);
		tol = strtok(NULL, "\n");
	}
	return (child_hex);
}

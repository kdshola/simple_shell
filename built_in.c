#include "main.h"

/**
 * get_built_in - checks and runs built in commands  if it exist
 * @cmd: user command and arguements
 * Return: adress of function or null
 */
int (*get_built_in(char **cmd))(char **argv, char *name)
{
	int i = 0;
	built_t command[] = {
		{"env", _env},
		{"exit", in_exit},
		{"cd", m_cd},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};

	for (i = 0; command[i].funct; i++)
	{
		if (_strcmp(cmd[0], command[i].funct) == 0)
			return (command[i].fptr);
	}
	return (NULL);
}

/**
 * in_exit - exits program
 * @args: program arguement vectors
 * @name: program name
 * Return: ) on sucess else -1
 */
int in_exit(char **args, char *name __attribute__((unused)))
{
	int status = 0;

	if (args[1])
	{
		if (is_fully_digits(args[1]) == true)
			status = _atoi(args[1]);
	}
	free_vectors(args);
	free_vectors(environ);
	exit(status);
	return (0);
}

/**
 * _env - prints current environment
 * @argv: arguement vector
 * @name: program name
 * Return: 0 on sucess else -1;
 */
int _env(char **argv, char *name)
{
	int i = 0;
	char message[150];

	if (argv[1])
	{
		_strcpy(message, "env");
		_strcat(message, ": ");
		_strcat(message, argv[1]);
		errno = ENOENT;
		print_error(message, name);
		return (-1);
	}
	while (environ[i])
	{
		_puts(environ[i]);
		i++;
	}
	return (0);
}

/**
 * m_cd - change directory
 * @argv: command with arguement
 * @name: program name
 * Return: exit status
 */
int m_cd(char **argv, char *name)
{
	int exit_stat = 0, error_no;
	char *prev_path = NULL, message[100], *dir[4], *buf = NULL;
	size_t length = 0;

	prev_path = _getenv("PWD");
	if (_strcmp(argv[1], "-") == 0)
		error_no = chdir(_getenv("OLDPWD"));
	else if (argv[1] == NULL || _strcmp(argv[1], "~") == 0)
		error_no = chdir(_getenv("HOME"));
	else
		error_no = chdir(argv[0]);
	if (error_no == -1)
	{
		create_message(message, "cd", argv[1]);
		print_error(message, name);
		return (-1);
	}
	exit_stat = error_no;
	dir[0] = NULL;
	dir[1] = "OLDPWD";
	dir[2] = prev_path;
	set_env(dir, name);
	dir[1] = "PWD";
	dir[2] = getcwd(buf, length);
	free(dir[2]);
	free(buf);
	return (exit_stat);
}

/**
 * m_echo - writes to stdout
 * @argv: program arguements
 * @ex_stat: exit status
 * Return: always 0
 */
int m_echo(char **argv, int ex_stat)
{
	int id = 0, i = 1;

	while (argv[i])
	{
		if (_strcmp(argv[i], "$$") == 0)
		{
			id = getpid();
			print_int(id);
		}
		else if (_strcmp(argv[i], "$?") == 0)
			print_int(ex_stat);
		else
			_puts(argv[i]);
		i++;
	}
	return (0);
}

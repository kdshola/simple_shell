#include "main.h"

/**
 * exit_error - exits on error
 * @argv: argument vector
 * Return: nothing
 */
void exit_error(char **argv)
{
	free_vectors(argv);
	free_vectors(environ);
	exit(-1);
}
/**
 * set_env - sets an environment variable
 * @argv: command wuth arguements
 * @name: program name
 * Return: ) on sucess else -1
 */
int set_env(char **argv, char *name)
{
	int i = 0, pos = 0;
	size_t length = 0;
	char message[150], *new = NULL, **env = environ;

	if (argv[1] == NULL || argv[2] == NULL)
		errno = EINVAL;
	if (errno == EINVAL)
	{
		(_strcpy(message, "env"), _strcat(message, ": "));
		_strcat(message, argv[1]);
		print_error(message, name);
		return (-1);
	}
	pos = get_pos(argv[1]);
	if (pos == -1)
	{
		i = add_env(argv[1], argv[2]);
		if (i == -1)
			(print_error("malloc", name), exit_error(argv));
		return (0);
	}
	length = _strlen(argv[1]) + _strlen(argv[2]);
	new = _realloc(env[pos], _strlen(env[pos]), length + 2);
	if (new == NULL)
	{
		(print_error("mallo", name), exit_error(argv));
		(_strcpy(new, argv[1]), _strcat(new, "="));
		_strcat(new, argv[2]);
		env[pos] = new;
	}
	return (0);
}

/**
 * unset_env - sets an environment variable
 * @argv: command wuth arguements
 * @name: program name
 * Return: 0 on success else -1
 */
int unset_env(char **argv, char *name)
{
	int pos = 0, len = 0;
	char message[150];

	if (argv[1] == NULL || argv[2])
		errno = EINVAL;
	if (_strlen(argv[1]) == 0)
		errno = EINVAL;
	if (errno == EINVAL)
	{
		(_strcpy(message, "env"), _strcat(message, ": "));
		print_error(message, name);
		return (-1);
	}
	pos = get_pos(argv[1]);
	if (pos == -1)
		return (0);
	len = env_length(environ);
	free(environ[pos]);
	for (; pos < len; pos++)
		environ[pos] = environ[pos + 1];
	return (0);
}

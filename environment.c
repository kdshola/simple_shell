#include "main.h"

/**
 * get_pos - finds position of an environmen variable
 * @env: environment variable
 * Return: varible position or NULL
 */
int get_pos(char *env)
{
	int j = 0, i = 0;

	if (env == NULL)
		return (-1);
	while (environ[i])
	{
		if (environ[i][j] == env[j])
		{
			for (j = 0; env[j]; j++)
			{
				if (env[j] != environ[i][j])
					break;
			}
			if (env[j] == '\0')
			{
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

/**
 * dup_env - duplicates environment array
 * @ptr: pointer to environment array
 * Return: pointer to new array or NULL
 */
char **dup_env(char **ptr)
{
	int length = 0, i = 0;
	char **dup = NULL;

	length = env_length(ptr);
	dup = malloc(sizeof(char *) * length + 3);
	if (ptr == NULL)
		return (NULL);
	while (ptr[i])
	{
		dup[i] = str_dup((const char *)ptr[i]);
		if (dup[i] == NULL)
		{
			for (; i > 0; i--)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}


/**
 * env_length - find length of the environment array
 * @_environ: pointer to environment array
 * Return: length of environment array
 */
int env_length(char **_environ)
{
	int length = 0;

	while (_environ[length])
	{
		length++;
	}
	return (length);
}

/**
 * add_env - adds environment variable
 * @name: variable name
 * @value: variable value
 * Return: 0 on sucess else -1
 */
int add_env(char *name, char *value)
{
	size_t name_len = 0, value_len = 0;
	int length = 0;
	char **env = NULL, *new = NULL;

	env = dup_env(environ);
	if (env == NULL)
		return (-1);
	length = env_length(env);
	name_len = _strlen((const char *)name);
	value_len = _strlen((const char *)value);
	new = malloc(sizeof(char) * (name_len + value_len + 2));
	if (new == NULL)
	{
		return (-1);
	}
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, (const char *)value);
	env[length++] = new;
	env[length] = NULL;
	free_vectors(environ);
	environ = env;
	return (0);
}

/**
 * init_environ - initializes environ variable with environment variabled
 * @name: program name
 * Return: nothing
 */
void init_environ(char *name)
{
	int pos = 0;
	size_t length = 0;
	char **env = NULL, **env_start = NULL, **current = NULL;

	env = environ;
	length = env_length(env);
	env_start = current = malloc(sizeof(char *) * length + 2);
	if (env_start == NULL)
	{
		print_error("malloc", name);
		exit(-1);
	}
	while (env[pos])
	{
		current[pos] = str_dup((const char *)env[pos]);
		if (current[pos] == NULL)
		{
			for (; pos >= 0; pos--)
				free(current[pos]);
			free(current);
			print_error("malloc", name);
			exit(-1);
		}
		pos++;
	}
	env[pos] = NULL;
	environ = env_start;
}

#include "main.h"

/**
 * _getenv - searches for an environment variable
 * @env: environment variable
 * Return: Returns pointer to value of variable else NULL if there is no match
 */
char *_getenv(const char *env)
{
	int j = 0, i = 0;

	if (env == NULL)
		return (NULL);
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
				j++;
				return (&environ[i][j]);
			}
		}
		i++;
	}
	return (NULL);
}

/**
 * get_binary - searches for binary files if it exist
 * @bin_name: name of binary
 * @program_name: name of program
 * Return: path to binary or null if it doesn't exist
 */

char *get_binary(char *bin_name, char *program_name)
{
	size_t dir_length = 0, bin_length = 0, path_length = 0;
	char *path = NULL, *path_dup = NULL, *path_token = NULL, *real_path = NULL;
	struct stat st;

	if (stat(bin_name, &st) == 0)
		return (bin_name);
	path = _getenv("PATH");
	if (path)
	{
		path_dup = str_dup((const char *)path);
		if (path_dup == NULL)
		{
			print_error("malloc", program_name);
			return (NULL);
		}
		bin_length = _strlen((const char *)bin_name);
		path_token = strtok(path_dup, ":");
		for (; path_token;)
		{
			dir_length = _strlen((const char *)path_token);
			path_length = dir_length + bin_length + 2;
			real_path = malloc(sizeof(char) * path_length);
			_strcpy(real_path, path_token);
			_strcat(real_path, "/");
			_strcat(real_path, (const char *)bin_name);
			if (stat(real_path, &st) == 0)
			{
				free(path_dup);
				return (real_path);
			}
			free(real_path);
			path_token = strtok(NULL, ":");

		}
		free(path_dup);
	}
	return (NULL);
}

/**
 * run_binary - executes a binary
 * @binary: binary name or path
 * @program_name: name of program
 * @input: user input
 * Return: void
 */

int run_binary(char **binary, char *program_name, char *input)
{
	int id, error, status, child_hex;
	char *bin_path = NULL;

	bin_path = get_binary(binary[0], program_name);
	if (bin_path == NULL)
	{
		error = errno;
		if (error == ENOMEM)
			(free_vectors(binary), _eof(2, program_name, &input));
		print_error(binary[0], program_name);
		return (-1);
	}
	id = fork();
	if (id == -1)
	{
		print_error("fork", program_name);
		return (-1);
	}
	if (id == 0)
		(execve(bin_path, binary, environ));
	else
	{
		if (wait(&status) == -1)
		{
			(print_error("wait", program_name), free(bin_path));
			return (-1);
		}
		free(bin_path);
		if (WIFEXITED(status) == true)
		{
			child_hex = WEXITSTATUS(status);
			return (child_hex);
		}
		print_error(binary[0], program_name);
		child_hex = errno;
	}
	return (child_hex);
}

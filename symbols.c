#include "main.h"

/**
 * find_symbol - finds a symbol
 * @input: user input
 * @symbol: symbol to find
 * Return: true or false
 */
bool find_symbol(char *input, char *symbol)
{
	int i, j = 0;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == symbol[j])
		{
			for (; symbol[j]; j++)
				if (input[i + j] != symbol[j])
					break;
			if (symbol[j] == '\0')
				return (true);
		}
	}
	return (false);
}

/**
 * handle_symbol - handles symbol
 * @name: program name
 * @input: user input
 * @exit_stat: exit status of program
 * Return: true or false
 */
bool handle_symbol(char *name, char *input, int *exit_stat)
{
	if (find_symbol(input, "||") == true)
	{
		*exit_stat = multiple(name, input, 1);
		return (true);
	}
	else if (find_symbol(input, "&&") == true)
	{
		*exit_stat = _and(name, input);
		return (true);
	}
	else if (find_symbol(input, ";") == true)
	{
		*exit_stat = multiple(name, input, 0);
		return (true);
	}
	return (false);
}

/**
 * multiple - executes multiple times
 * @name: program name
 * @input: user input
 * @flag: flag
 * Return: exit status
 */
int multiple(char *name, char *input, int flag)
{
	int (*fp)(char **, char *), exit_stat;
	char *token = NULL, *delim = "||", **args = NULL, *tmp = input;

	if (flag == 0)
		delim = ";";
	token = strtok(input, delim);
	while (token)
	{
		args = tokenize(" ", token, name);
		if (is_echo(args, exit_stat, &exit_stat) == true)
		{
			token = strtok(NULL, delim);
			continue;
		}
		fp = get_built_in(args);
		if (fp)
		{
			exit_stat = fp(args, name);
			free_vectors(args);
			token = strtok(NULL, delim);
			continue;
		}
		exit_stat = run_binary(args, name, tmp);
		free(args);
		token = strtok(NULL, delim);
	}
	return (exit_stat);
}

/**
 * _and - executes multiple times
 * @name: program name
 * @input: user input
 * Return: exit status
 */
int _and(char *name, char *input)
{
	int (*fp)(char **, char *), exit_stat;
	char *token = NULL, *delim = "&&", **args = NULL, *tmp = input;

	token = strtok(input, delim);
	while (token)
	{
		args = tokenize(" ", token, name);
		if (is_echo(args, exit_stat, &exit_stat) == true)
		{
			if (exit_stat == -1)
			{
				free_vectors(args);
				return (-1);
			}
			token = strtok(NULL, delim);
			continue;
		}
		fp = get_built_in(args);
		if (fp)
		{
			exit_stat = fp(args, name);
			if (exit_stat == -1)
			{
				free_vectors(args);
				return (-1);
			}
			free_vectors(args), token = strtok(NULL, delim);
			continue;
		}
		exit_stat = run_binary(args, name, tmp);
		{
			if (exit_stat == -1)
			{
				free_vectors(args);
				return (-1);
			}
			free_vectors(args), token = strtok(NULL, delim);
		}
		free(args);
		token = strtok(NULL, delim);
	}
	return (exit_stat);
}

#include "main.h"

/**
 * is_echo - checks for echo command
 * @argv: command and arguements
 * @exit_stat: program exit status
 * @ex_stat: adress of exit status variable
 * Return: true of false
 */
bool is_echo(char **argv, int exit_stat, int *ex_stat)
{
	if (_strcmp(argv[0], "echo") == 0)
	{
		m_echo(argv, exit_stat);
		free_vectors(argv);
		*ex_stat = 0;
		_putchar('\n');
		return (true);
	}
	return (false);
}

/**
 * isprintable - checks if string contains printable character
 * @str: string
 * Return: true if printable else false
 */
bool isprintable(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
		if (str[i] >= 32)
			return (true);
	return (false);
}

/**
 * _allocate - creates buffer to stor duplicate user input
 * @input: user input
 * @name: program name
 * Return: Returns pointer to duplicate input else NULL
 */
char *_allocate(const char *name, char *input)
{
	char *dup = NULL;

	dup = malloc(sizeof(char) * (_strlen(input) + 1));
	if (dup == NULL)
	{
		_eof(2, name, &input);
	}
	return (dup);
}

/**
 * _eof - checks for eof character
 * @status: input status
 * @name: program name
 * @input: input buffer address
 * Return: void
 */
void _eof(int status, const char *name, char **input)
{
	int error;

	free_vectors(environ);
	error = errno;
	if (status == 2 || error == ENOMEM)
	{
		print_error("malloc", (char *)name);
		free(*input);
		*input = NULL;
		exit(-1);
	}
	else
	{
		free(*input);
		*input = NULL;
		exit(-1);
	}
}

/**
 * main - entry point for simple shell program
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 Always
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	size_t buffer_size = 0;
	ssize_t input_read;
	char *user_input = NULL, **tokens = NULL;
	int (*fp)(char **, char *), child_hex = 0;

	init_environ(argv[0]);
	if (argv[1])
	{
		child_hex = noninteractive(argv[0], argv[1]);
		return (child_hex);
	}
	while (true)
	{
		if (isatty(0))
			write(1, "$ ", 2);
		input_read = getline(&user_input, &buffer_size, stdin);
		if (input_read == -1)
			_eof(input_read, argv[0], &user_input);
		if (input_read > 0)
		{
			if (isprintable(user_input) == true)
			{
				handle_hash(user_input);
				if (handle_symbol(argv[0], user_input, &child_hex) == true)
					continue;
				tokens = tokenize(" \n", user_input, argv[0]);
				if (is_echo(tokens, child_hex, &child_hex) == true)
					continue;
				fp = get_built_in(tokens);
				if (fp)
				{
					child_hex = fp(tokens, argv[0]), free_vectors(tokens);
					continue;
				}
			child_hex = run_binary(tokens, argv[0], user_input);
			free_vectors(tokens);
			}
		}
	}
	return (0);
}

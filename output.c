#include "main.h"

/**
 * _putchar - writes a character to stdout
 * @c: charater to write
 * Return: )mon sucess else -1
 */
int _putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * _puts - writes string to stdout
 * @str: string to write
 * Return: nothing
 */
void _puts(char *str)
{
	int i = 0;

	for (i = 0; str[i]; i++)
		_putchar(str[i]);
	_putchar('\n');
}

/**
 * _prompt - prints prompt to stdout
 * @name: program name
 * Return: void
 */
void _prompt(char *name)
{
	char prompt[] = "$ ";
	int written_chars = 0;
	char error_message[50];

	written_chars = write(STDOUT_FILENO, prompt, 2);
	if (written_chars == -1)
	{
		_strcat(error_message, name);
		_strcat(error_message, ": ");
		_strcat(error_message, "write");
		perror(error_message);
		written_chars = write(STDOUT_FILENO, prompt, 2);
	}
}

/**
 * print_error - Prints error message
 * @cause: cause of error
 * @program: program name
 * Return: Nothing
 */
void print_error(char *cause, char *program)
{
	char message[150];

	_strcat(message, program);
	_strcat(message, ": ");
	_strcat(message, cause);
	perror(message);

}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 if both are equal, positive if first different character is
 * greater in s1 negative for vice versa
 */
int _strcmp(char *s1, char *s2)
{
	int i, ret_val = 0;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			ret_val = s1[i] - s2[i];
			break;
		}
	}
	return (ret_val);
}

#include "main.h"

/**
 * handle_hash - handles comment in command
 * @command: program command
 * Retuen: Nothing
 */
void handle_hash(char *command)
{
	int i;

	for (i = 0; command[i]; i++)
	{
		if (command[i] == '#')
			command[i] = '\0';
	}
}

/**
 * is_fully_digits - checks if a string contains only digits
 * @str: string to check
 * Return: true or false
 */
bool is_fully_digits(char *str)
{
	int i = 0;

	if (str[0] == '-')
		i++;
	for (; str[i]; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			continue;
		else
			return (false);
	}
	return (true);
}

/**
 * _atoi - converts a string to an integer
 * @string: string to convert to integer
 * Return: integer value
 */

int _atoi(char *string)
{
	int num = 0;
	int sign = 1;

	do {
		if (*string == '-')
			sign *= -1;
		else if (*string >= '0' && *string <= '9')
			num = (num * 10) + (*string - '0');
		else
			break;
	} while (*string++);
	num *= sign;
	return (num);
}

/**
 * print_int - prints an integer to stdout
 * @number: number to print
 * Return: Nothing
 */
void print_int(int number)
{
	if (number < 0)
	{
		_putchar('-');
		number = -number;
	}
	if (number / 10)
		print_int(number / 10);
	_putchar((number % 10) + '0');
}

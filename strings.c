#include "main.h"

/**
 * _strcpy - copies sting from source to dest
 * @src: source
 * @dest: destination
 * Return: Nothing
 */
void _strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}

/**
 * _strlen - finds length of a string
 * @str: string
 * Return: string length
 */
size_t _strlen(const char *str)
{
	size_t length = 0;

	while (str[length])
		length++;
	return (length);
}

/**
 * _strcat - concatenates source string to destination
 * @dest: destination buffer
 * @src: source string
 * Return: void
 */

void _strcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest[i]; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
}

/**
 * count_tokens - count number of tokens
 * @input: user input
 * @delimiter: string delimiter
 * Return: number of tokens
 */
int count_tokens(char *input, const char *delimiter)
{
	int token_count = 0;
	char *token_ptr = NULL;

	token_ptr = strtok(input, delimiter);
	while (token_ptr)
	{
		token_count++;
		token_ptr = strtok(NULL, delimiter);
	}
	token_count++;
	return (token_count);
}
/**
 * str_dup - duplicates given memory
 * @buffer: memory to duplicete
 * Return: dupicate memory or NULL
 */
char *str_dup(const char *buffer)
{
	unsigned int i;
	char *dup = NULL;

	dup = malloc(sizeof(char) * (_strlen(buffer) + 1));
	if (dup == NULL)
		return (NULL);
	for (i = 0; buffer[i]; i++)
		dup[i] = buffer[i];
	dup[i] = '\0';
	return (dup);
}

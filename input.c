#include "main.h"

/**
 * is_delim - checks if character is part of delimiter
 * @c: character to check for
 * @delim: string delimeter
 * Return: true if c is part of delimiter else false
 */
bool is_delim(char c, const char *delim)
{
	int i;

	for (i = 0; delim[i]; i++)
	{
		if (c == delim[i])
			return (true);
	}
	return (false);
}

/**
 * m_getline - reads data from given file descriptor
 * @lineptr: buffer to store read data
 * @n: buffer size
 * @fd: file descriptor to read from
 * Return: number of input read
 */
ssize_t m_getline(char **lineptr, size_t *n, int fd)
{
	ssize_t read_chars = 1024, total_read = 0;
	char temp[INPUT_BUFFER_SIZE + 1], *tmp = NULL;
	static char *save_ptr;

	if (*lineptr == NULL && *n == 0)
	{
		*lineptr = malloc(sizeof(char) * INPUT_BUFFER_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = INPUT_BUFFER_SIZE;
	}
	if (save_ptr && *n != 0)
		*lineptr = save_ptr;
	*lineptr[0] = '\0';
	while (read_chars == 1024)
	{
		read_chars = read(fd, temp, 1024);
		total_read += read_chars;
		if (read_chars == -1)
			break;
		if (read_chars == INPUT_BUFFER_SIZE)
		{
			tmp = _realloc(*lineptr, *n, (*n + INPUT_BUFFER_SIZE));
			if (tmp == NULL)
			{
				save_ptr = NULL;
				return (-1);
			}
			*lineptr = tmp;
			*n += INPUT_BUFFER_SIZE;
		}
		temp[read_chars] = '\0';
		_strcat(*lineptr, temp);
		if (total_read > 0 && *lineptr[total_read - 1] == '\n')
			break;
	}
	total_read = (errno = EINTR) ? total_read : -1;
	save_ptr = *lineptr;
	return (total_read);
}

/**
 * m_strtok - creates string token base on characters in delim
 * @str: string to tokenize
 * @delim: delimiter used to split string into tokens
 * Return: pointer to the first token an then the next or NULL after string end
 */
char *m_strtok(char *str, const char *delim)
{
	char *token_ptr = NULL;
	static char *save_ptr;

	if (str == NULL && save_ptr == NULL)
		return (NULL);
	if (str == NULL && save_ptr != NULL)
	{
		str = save_ptr;
	}
	for (; *str; str++)
	{
		if (is_delim(*str, (const char *)delim) == true)
		{
			*str = '\0';
			continue;
		}
		else
		{
			token_ptr = str;
			break;
		}
	}
	for (; *str; str++)
	{
		if (is_delim(*str, (const char *)delim) == false)
			continue;
		else
		{
			*str = '\0';
			save_ptr = str + 1;
			break;
		}
	}
	if (*(str + 1) == '\0')
		save_ptr = NULL;
	return (token_ptr);
}

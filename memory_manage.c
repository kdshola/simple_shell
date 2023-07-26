#include "main.h"

/**
 * tokenize - creates tokens from user input
 * @delim: delimiter characters
 * @input: user input
 * @program_name: name of program
 * Return: Token vectors
 */
char **tokenize(char *delim, char *input, char *program_name)
{
	char **tokens = NULL;
	char *tok = NULL, *copy = NULL;
	int i, j = 0, token_num = 0;

	copy = _allocate(program_name, input);
	_strcpy(copy, input);
	token_num = count_tokens(input, (const char *)delim);
	tokens = malloc(sizeof(char *) * token_num);
	if (tokens == NULL)
		_eof(2, program_name, &input);

	tok = strtok(copy, delim);
	for (i = 0; tok != NULL; i++)
	{
		tokens[i] = malloc(sizeof(char) * (_strlen(tok) + 1));
		if (tokens[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(tokens[j]);
			}
			free(tokens);
			free(copy);
			_eof(2, program_name, &input);
		}
		_strcpy(tokens[i], tok);
		tok = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	free(copy);
	return (tokens);
}

/**
 * free_vectors - frees an array of strings
 * @vectors: string array
 * Return: Nothing
 */
void free_vectors(char **vectors)
{
	int i = 0;

	while (vectors[i])
	{
		free(vectors[i]);
		i++;
	}
	free(vectors);
}

/**
 * _realloc - reallocates a block of memorry
 * @ptr: pointer to memory to resize
 * @new_size: newize
 * @old_size: size of old memory block
 * Return: NULL on failure
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t i;
	char *new_ptr = NULL, *copy = (char *)ptr;

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < old_size; i++)
	{
		new_ptr[i] = copy[i];
	}
	free(ptr);
	return ((void *)new_ptr);
}

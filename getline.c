#include "shell.h"

/**
 * _getline - Reads characters from the stream
 * @lineptr: Pointer to the character
 * @n: Size of the pointer
 * @stream: Where to read characters from
 * Return: Return number of character read
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i;
	char buffer[1024];


	if (*lineptr == NULL || *n == 0)
	{
		*n = 256;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
		{
			perror("Allocation failed");
		}
	}

	if (fgets(buffer, sizeof(buffer), stream) != NULL)
	{
		while (buffer[i] != '\n')
		{
			i++;
		}
	}
	i += 1;
	if (feof(stream))
		return (-1);
	if (ferror(stream))
		exit(EXIT_FAILURE);
	while (i >= *n)
	{
		*n += 128;
		*lineptr = realloc(*lineptr, *n);
	}
	if ((*lineptr) == NULL)
	{
		perror("Allocation failed ");
		return (-1);
	}
	strncpy(*lineptr, buffer, i);
	i += 1;
	(*lineptr)[i] = '\0';
	return (i);
}

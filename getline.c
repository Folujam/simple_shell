#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * _getline - Reads characters from the stream
 * @lineptr: Pointer to the character
 * @n: Size of the pointer
 * @stream: Where to read characters from
 * Return: Return number of character read
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i, j, k;
	char buffer[1024];

	k = 0;
	i = fread(buffer, sizeof(char), 1024, stream);
	while ((i != -1))
	{
		if (i < 1024)
		{
			if (feof(stream))
				return (i);
			if (ferror(stream))
				exit(EXIT_FAILURE);
		}
		*n += i;
		k += i;
		if (*n == k)
		{
			*lineptr = realloc(*lineptr, *n);
			if ((*lineptr) == NULL)
			{
				perror("Allocation failed ");
				return (-1);
			}
		}
		for (j = 0; j < i; j++)
			*lineptr[j] = buffer[j];
		k += i;
	}
	else
		return (-1)
	(*lineptr)[j + 1] = '\0';
	return (k);
}

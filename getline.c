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
	size_t i;
	char c;

	i = 0;
	while ((c = getc(stream)) != EOF)
	{
		if (i >= *n)
		{
			n += 1;
			*lineptr = realloc(*lineptr, *n);
			if ((*lineptr) == NULL)
			{
				perror("Allocation failed ");
				return (-1);
			}
		}
		(*lineptr)[i] = c;
		i++;
	}
	(*lineptr)[i + 1] = '\0';
	return (i);
}

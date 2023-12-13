#include "shell.h"

/**
 * _strncat - Concatenates two strings up to a specified limit.
 * @destination: The first string.
 * @source: The second string to append.
 * @limit: The maximum number of bytes to concatenate.
 *
 * Return: Returns the pointer to the concatenated string.
 */
char *_strncat(char *destination, char *source, int limit)
{
	int index_dest = 0, index_src = 0;
	char *result = destination;

	while (destination[index_dest] != '\0')
		index_dest++;

	while (source[index_src] != '\0' && index_src < limit)
	{
		destination[index_dest] = source[index_src];
		index_dest++;
		index_src++;
	}

	if (index_src < limit)
		destination[index_dest] = '\0';

	return (result);
}

/**
 * _strncpy - Copies a string up to a specified limit.
 * @destination: The destination string to be copied to.
 * @source: The source string to copy from.
 * @limit: The maximum number of characters to copy.
 *
 * Return: Returns the pointer to the concatenated string.
 */
char *_strncpy(char *destination, char *source, int limit)
{
	int index_dest = 0, index_src = 0;
	char *result = destination;

	while (source[index_src] != '\0' && index_src < limit - 1)
	{
		destination[index_dest] = source[index_src];
		index_dest++;
		index_src++;
	}

	if (index_src < limit)
	{
		int j = index_src;

		while (j < limit)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}
/**
 * _strchr - Locates a character in a string.
 * @string: The string to be parsed.
 * @character: The character to look for
 * Return: Returns a pointer to the first occurrence of the character in the
 * string.
 */
char *_strchr(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

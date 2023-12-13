#include "shell.h"

/**
 * _putsfd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: Returns the number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += _putfd(*str++, fd);
	}
	return (count);
}

/**
 * _eputchar - Writes the character c to stderr.
 * @ch: The character to print.
 *
 * Return: Returns 1 on success, -1 on error.
 */
int _eputchar(char ch)
{
	static int count;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(2, buffer, count);
		count = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[count++] = ch;
	return (1);
}

/**
 * _eputs - Prints an input string to stderr.
 * @cstr: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *cstr)
{
	int index = 0;

	if (!cstr)
		return;
	while (cstr[index] != '\0')
	{
		_eputchar(cstr[index]);
		index++;
	}
}

/**
 * _putfd - Writes the character c to the given file descriptor.
 * @ch: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: Returns 1 on success, -1 on error.
 */
int _putfd(char ch, int fd)
{
	static int count;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, count);
		count = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[count++] = ch;
	return (1);
}

#include "shell.h"
/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: The address of the string to modify.
 * Return: Always returns 0.
 */
void remove_comments(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
	{
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
	}
}

/**
 * _erratoi - Converts a string to an integer.
 * @str: The string to be converted.
 * Return: Returns 0 if no nums in the str, otherwise -1 on error.
 */
int _erratoi(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++; /* Skips the positive sign if present. */

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1); /* Indicates overflow error. */
		}
		else
			return (-1); /* Indicates invalid characters in the string. */
	}
	return (result);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number to print.
 * @fd: The file descriptor to write to.
 * Return: Returns the number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int abs_val, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	if (input < 0)
	{
		abs_val = -input;
		__putchar('-');
		count++;
	}
	else
		abs_val = input;

	current = abs_val;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (abs_val / index)
		{
			__putchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * print_error - Prints an error message.
 * @info: The parameter & return info struct.
 * @estr: String containing specified error type.
 * Return: Nothing.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * convert_number - Converter function, a clone of itoa.
 * @numb: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 * Return: Returns the converted string.
 */
char *convert_number(long int numb, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long nu = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		nu = -numb;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[nu % base];
		nu /= base;
	} while (nu != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

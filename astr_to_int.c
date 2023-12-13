#include "shell.h"

/**
 * interactive - Checks if the shell operates in interactive mode
 * @info: Pointer to the info_t struct
 *
 * Return: 1 if operating in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter
 * @ch: The character to check
 * @delimiter: The string containing delimiters
 *
 * Return: 1 if it's a delimiter, 0 otherwise
 */
int is_delim(char ch, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == ch)
			return (1);
	return (0);
}

/**
 * _isalpha - Checks if a character is alphabetic
 * @ch: The character to check
 *
 * Return: 1 if 'ch' is alphabetic and 0 otherwise
 */
int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: 0 if no numbers in the string, converted number otherwise
 */
int _atoi(char *str)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


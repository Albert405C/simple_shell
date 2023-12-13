#include "shell.h"

/**
 * get_input - gets a line minus the newline
 * @info: parameter structure
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t index_i, index_j, length;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(info->arg), *position;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &buffer, &length);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (length)
	{
		index_j = index_i;
		position = buffer + index_i; /* get pointer for return */

		check_chain(info, buffer, &index_j, index_i, length);
		while (index_j < length)
		{
			if (is_chain(info, buffer, &index_j))
				break;
			index_j++;
		}

		index_i = index_j + 1; /* increment past nulled ';' */
		if (index_i >= length) /* reached end of buffer? */
		{
			index_i = length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_ptr = position; /* pass back pointer to current command position */
		return (_strlen(position)); /* return length of current command */
	}

	*buffer_ptr = buffer;
	return (bytes_read); /* return length of buffer from _getline() */
}

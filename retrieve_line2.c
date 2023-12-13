#include "shell.h"

/**
 * sigintHandler - handles ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * input_buf - buffers chained commands
 * @info: parameter structure
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: number of bytes read
 */
ssize_t input_buf(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t length_ptr = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &length_ptr, stdin);
#else
		bytes_read = _getline(info, buffer, &length_ptr);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			/* Check for command chain */
			{
				*length = bytes_read;
				info->cmd_buf = buffer;
			}
		}
	}
	return (bytes_read);
}

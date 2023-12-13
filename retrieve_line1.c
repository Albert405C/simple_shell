#include "shell.h"

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t index_i, len;
	size_t k;
	ssize_t r = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (index_i == len)
		index_i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + index_i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, size, size ? size + k : k + 1);
	if (!new_p) /* Memory allocation failure */
		return (p ? (free(p), -1) : -1);

	if (size)
		_strncat(new_p, buf + index_i, k - index_i);
	else
		_strncpy(new_p, buf + index_i, k - index_i + 1);

	size += k - index_i;
	index_i = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return (size);
}

/**
 * read_buf - reads a buffer
 * @info: parameter structure
 * @buffer: buffer
 * @size: size
 *
 * Return: bytes read
 */
ssize_t read_buf(info_t *info, char *buffer, size_t *size)
{
	ssize_t bytes_read = 0;

	if (*size)
		return (0);
	bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*size = bytes_read;
	return (bytes_read);
}

#include "shell.h"

/**
 * get_history_file - obtains the history file path
 * @info: parameter structure
 * Return: string containing allocated history file path
 */
char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * renumber_history - renumbers the history linked list after modifications
 * @info: parameter structure for maintaining arguments
 * Return: the updated histcount
 */
int renumber_history(info_t *info)
{
	list_t *nnode = info->history;
	int count = 0;

	while (nnode)
	{
		nnode->num = count++;
		nnode = nnode->next;
	}
	return (info->histcount = count);
}

/**
 * write_history - creates or appends to a history file
 * @info: parameter structure
 * Return: 1 on success, -1 otherwise
 */
int write_history(info_t *info)
{
	ssize_t file_descriptor;
	char *file_name = get_history_file(info);
	list_t *c_node = NULL;

	if (!file_name)
		return (-1);

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
		return (-1);
	for (c_node = info->history; c_node; c_node = c_node->next)
	{
		_putsfd(c_node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

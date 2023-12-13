#include "shell.h"

/**
 * build_history_list - appends an entry to a history linked list
 * @info: parameter structure for maintaining arguments
 * @buffer: buffer containing history entry
 * @line_count: history line count
 * Return: Always returns 0
 */
int build_history_list(info_t *info, char *buffer, int line_count)
{
	list_t *nnode = NULL;

	if (info->history)
		nnode = info->history;
	add_node_end(&nnode, buffer, line_count);

	if (!info->history)
		info->history = nnode;
	return (0);
}

/**
 * read_history - reads a files history
 * @info: parameter structure
 * Return: histcount on succes and 0 otherwise
 */
int read_history(info_t *info)
{
	int index, last_index = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	char *buffer = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (index = 0; index < file_size; index++)
		if (buffer[index] == '\n')
		{
			buffer[index] = 0;
			build_history_list(info, buffer + last_index, line_count++);
			last_index = index + 1;
		}
	if (last_index != index)
		build_history_list(info, buffer + last_index, line_count++);
	free(buffer);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

#include "shell.h"
/**
 * _myalias - Mimics the behavior of the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0
 */
int _myalias(info_t *info)
{
	int index = 0;
	char *position = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		position = _strchr(info->argv[index], '=');
		if (position)
			set_alias(info, info->argv[index]);
		else
			print_alias(node_starts_with(info->alias, info->argv[index], '='));
	}

	return (0);
}

/**
 * unset_alias - Removes an alias.
 * @info: Parameter structure.
 * @str: The string alias to be unset.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *position, storedChar;
	int result;

	position = _strchr(str, '=');
	if (!position)
		return (1);
	storedChar = *position;
	*position = 0;
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*position = storedChar;
	return (result);
}

/**
 * _myhistory - Displays command hist list, each command on a separate line,
 * numbered from 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always returns 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * print_alias - Prints an alias string.
 * @node: Alias node.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *position = NULL, *alias = NULL;

	if (node)
	{
		position = _strchr(node->str, '=');
		for (alias = node->str; alias <= position; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(position + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * set_alias - Sets an alias.
 * @info: Parameter structure.
 * @str: The string alias to be set.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *position;

	position = _strchr(str, '=');
	if (!position)
		return (1);
	if (!*++position)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

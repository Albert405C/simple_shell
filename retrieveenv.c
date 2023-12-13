#include "shell.h"

/**
 * _setenv - Initializes or modifies an environment variable
 * @info: A structure containing possible arguments,
 * maintaining the function prototype.
 * @variable: The environment variable property
 * @value: The environment variable value
 *
 * Return: Always returns 0
 */
int _setenv(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, variable);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - Deletes an environment variable
 * @info: A structure containing possible arguments,
 * maintaining the function prototype.
 * @variable: The environment variable property to delete
 * Return: Returns 1 on deletion, 0 otherwise
 */
int _unsetenv(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *ptr;

	if (!node || !variable)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, variable);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * get_environ - Provides a copy of our environment strings
 * @info: A structure containing possible arguments,
 * maintaining the function prototype.
 * Return: Always returns 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

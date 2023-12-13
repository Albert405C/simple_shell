#include "shell.h"
/**
 * populate_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always returns 0.
 */
int populate_env_list(info_t *info)
{
	list_t *env_node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_node_end(&env_node, environ[index], 0);
	info->env = env_node;
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 * Return: Returns the value of the variable.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *current_node = info->env;
	char *ptr;

	while (current_node)
	{
		ptr = starts_with(current_node->str, name);
		if (ptr && *ptr)
			return (ptr);
		current_node = current_node->next;
	}
	return (NULL);
}


/**
 * _myenv - Displays the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always returns 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _myunsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always returns 0.
 */
int _myunsetenv(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		_unsetenv(info, info->argv[index]);

	return (0);
}

/**
 * _mysetenv - Initializes new env variable or modifies an existing one.
 * @info: Structure containing potential arguments.
 * Return: Returns 0 on success, 1 on failure.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

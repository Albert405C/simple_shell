#include "shell.h"

/**
 * clear_info - Initializes info_t structure fields
 * @info: Address of the structure
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * free_info - Deallocates info_t structure fields
 * @info: Address of the structure
 * @all_fields: True if freeing all fields
 */
void free_info(info_t *info, int all_fields)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all_fields)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * set_info - Sets up info_t structure
 * @info: Address of the structure
 * @args_vector: Argument vector
 */
void set_info(info_t *info, char **args_vector)
{
	int index = 0;

	info->fname = args_vector[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (index = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

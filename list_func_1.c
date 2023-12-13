#include "shell.h"

/**
 * delete_node_at_index - Function deletes node at given position
 * @head_ptr: pointer to first node address
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head_ptr, unsigned int index)
{
	list_t *node, *p_node;
	unsigned int count = 0;

	if (!head_ptr || !*head_ptr)
		return (0);

	if (!index)
	{
		node = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head_ptr;
	while (node)
	{
		if (count == index)
		{
			p_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		count++;
		p_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * add_node_end - Function adds a node to the end of list
 * @head_ptr: pointer to head node address
 * @string: string field of node
 * @index: node index to be used by history
 * Return: pointer to the newly added node
 */
list_t *add_node_end(list_t **head_ptr, const char *string, int index)
{
	list_t *new_node, *current_node;

	if (!head_ptr)
		return (NULL);

	current_node = *head_ptr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;
	if (string)
	{
		new_node->str = _strdup(string);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
		*head_ptr = new_node;
	return (new_node);
}

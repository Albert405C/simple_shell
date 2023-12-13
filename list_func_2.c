#include "shell.h"

/**
 * free_list - To free all nodes of a linked list
 * @hd_ptr:  pointer to head node address
 * Return: void
 */
void free_list(list_t **hd_ptr)
{
	list_t *node, *n_node, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		n_node = node->next;
		free(node->str);
		free(node);
		node = n_node;
	}
	*hd_ptr = NULL;
}

/**
 * add_node - Add a node to start of linked list
 * @head_ptr: pointer to head node address
 * @string: string field of node
 * @index: node index used by history
 *
 * Return: pointer to the newly added node
 */
list_t *add_node(list_t **head_ptr, const char *string, int index)
{
	list_t *new_head;

	if (!head_ptr)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = index;
	if (string)
	{
		new_head->str = _strdup(string);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head_ptr;
	*head_ptr = new_head;
	return (new_head);
}

/**
 * print_list_str - prints only the string element of a list_t linked list
 * @node: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *node)
{
	size_t count = 0;

	while (node)
	{
		_puts(node->str ? node->str : "(nil)");
		_puts("\n");
		node = node->next;
		count++;
	}
	return (count);
}

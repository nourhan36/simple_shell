#include "shell.h"

/**
 * add_list_node - adds a node to the start of the list
 * @list_head: address of pointer to list head node
 * @string: string field of node
 * @index: node index used by history
 *
 * Return: size of list
 */
list_t *add_list_node(list_t **list_head, const char *string, int index)
{
	list_t *new_head;

	if (!list_head)
		return NULL;
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return NULL;
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->index = index;
	if (string)
	{
		new_head->string = _strdup(string);
		if (!new_head->string)
		{
			free(new_head);
			return NULL;
		}
	}
	new_head->next = *list_head;
	*list_head = new_head;
	return new_head;
}

/**
 * add_list_node_end - adds a node to the end of the list
 * @list_head: address of pointer to list head node
 * @string: string field of node
 * @index: node index used by history
 *
 * Return: size of list
 */
list_t *add_list_node_end(list_t **list_head, const char *string, int index)
{
	list_t *new_node, *node;

	if (!list_head)
		return NULL;

	node = *list_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (string)
	{
		new_node->string = _strdup(string);
		if (!new_node->string)
		{
			free(new_node);
			return NULL;
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*list_head = new_node;
	return new_node;
}

/**
 * print_list_string - prints only the string element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_string(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->string ? head->string : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return count;
}

/**
 * delete_node_at_index - deletes node at given index
 * @list_head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **list_head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int count = 0;

	if (!list_head || !*list_head)
		return 0;

	if (!index)
	{
		node = *list_head;
		*list_head = (*list_head)->next;
		free(node->string);
		free(node);
		return 1;
	}
	node = *list_head;
	while (node)
	{
		if (count == index)
		{
			prev_node->next = node->next;
			free(node->string);
			free(node);
			return 1;
		}
		count++;
		prev_node = node;
		node = node->next;
	}
	return 0;
}

/**
 * free_list_nodes - frees all nodes of a list
 * @list_head_ptr: address of pointer to list head node
 *
 * Return: void
 */
void free_list_nodes(list_t **list_head_ptr)
{
	list_t *node, *next_node, *head;

	if (!list_head_ptr || !*list_head_ptr)
		return;
	head = *list_head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->string);
		free(node);
		node = next_node;
	}
	*list_head_ptr = NULL;
}


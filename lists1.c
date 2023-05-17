#include "shell.h"

/**
 * get_list_length - determines the length of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t get_list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - returns an array of strings from the list's str values
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t length = get_list_length(head), i;
	char **strings;
	char *string;

	if (!head || !length)
		return (NULL);

	strings = malloc(sizeof(char *) * (length + 1));
	if (!strings)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		string = malloc(_strlen(node->str) + 1);
		if (!string)
		{
			for (; i > 0; i--)
				free(strings[i - 1]);
			free(strings);
			return (NULL);
		}

		_strcpy(string, node->str);
		strings[i] = string;
	}
	strings[i] = NULL;
	return (strings);
}


/**
 * print_list - prints all elements of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * find_node_starts_with - returns the node whose string starts with a prefix
 * @node: pointer to the head of the list
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matched node or NULL
 */
list_t *find_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node in a linked list
 * @head: pointer to the head of the list
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

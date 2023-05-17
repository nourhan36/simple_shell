#include "shell.h"

/**
 * _custom_history - displays the history list, one command by line, preceded
 *                   with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _custom_history(info_t *data)
{
	print_list(data->command_history);
	return (0);
}

/**
 * unset_custom_alias - removes an alias from the alias list
 * @data: parameter struct
 * @str: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_custom_alias(info_t *data, char *str)
{
	char *p, c;
	int ret;

	p = _custom_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(data->custom_alias),
		get_node_index(data->custom_alias, node_starts_with(data->custom_alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_custom_alias - sets an alias to a string
 * @data: parameter struct
 * @str: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int set_custom_alias(info_t *data, char *str)
{
	char *p;

	p = _custom_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_custom_alias(data, str));

	unset_custom_alias(data, str);
	return (add_node_end(&(data->custom_alias), str, 0) == NULL);
}

/**
 * print_custom_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_custom_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _custom_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_custom_putchar(*a);
		_custom_putchar('\'');
		_custom_puts(p + 1);
		_custom_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _custom_alias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _custom_alias(info_t *data)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->custom_alias;
		while (node)
		{
			print_custom_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = _custom_strchr(data->argv[i], '=');
		if (p)
			set_custom_alias(data, data->argv[i]);
		else
			print_custom_alias(node_starts_with(data->custom_alias, data->argv[i], '='));
	}

	return (0);
}


#include "shell.h"

/**
 * _custom_env - prints the current environment
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _custom_env(info_t *data)
{
	print_list_str(data->environment);
	return (0);
}

/**
 * _custom_getenv - gets the value of an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: the value of the environment variable
 */
char *_custom_getenv(info_t *data, const char *name)
{
	list_t *node = data->environment;
	char *p;

	while (node)
	{
		p = custom_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _custom_setenv - Initialize a new environment variable,
 *                  or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _custom_setenv(info_t *data)
{
	if (data->argc != 3)
	{
		_custom_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_custom_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * _custom_unsetenv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _custom_unsetenv(info_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_custom_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		_custom_unsetenv(data, data->argv[i]);

	return (0);
}

/**
 * populate_custom_env_list - populates environment linked list
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_custom_env_list(info_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; custom_environ[i]; i++)
		add_custom_node_end(&node, custom_environ[i], 0);
	data->environment = node;
	return (0);
}


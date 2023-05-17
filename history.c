#include "shell.h"

/**
 * get_shell_history_file - gets the history file
 * @shell_info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_shell_history_file(shell_info_t *shell_info)
{
	char *buffer, *directory;

	directory = _getenv(shell_info, "HOME=");
	if (!directory)
		return NULL;
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return NULL;
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return buffer;
}

/**
 * write_shell_history - creates a file, or appends to an existing file
 * @shell_info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_shell_history(shell_info_t *shell_info)
{
	ssize_t file_descriptor;
	char *filename = get_shell_history_file(shell_info);
	list_t *node = NULL;

	if (!filename)
		return -1;

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return -1;
	for (node = shell_info->history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return 1;
}

/**
 * read_shell_history - reads history from file
 * @shell_info: the parameter struct
 *
 * Return: history count on success, 0 otherwise
 */
int read_shell_history(shell_info_t *shell_info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat statistics;
	char *buffer = NULL, *filename = get_shell_history_file(shell_info);

	if (!filename)
		return 0;

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return 0;
	if (!fstat(file_descriptor, &statistics))
		file_size = statistics.st_size;
	if (file_size < 2)
		return 0;
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return 0;
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return free(buffer), 0;
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_shell_history_list(shell_info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_shell_history_list(shell_info, buffer + last, line_count++);
	free(buffer);
	shell_info->history_count = line_count;
	while (shell_info->history_count-- >= HIST_MAX)
		delete_node_at_index(&(shell_info->history), 0);
	renumber_shell_history(shell_info);
	return shell_info->history_count;
}

/**
 * build_shell_history_list - adds entry to a history linked list
 * @shell_info: Structure containing potential arguments
 * @buffer: buffer
 * @line_count: the history line count, history_count
 *
 * Return: Always 0
 */
int build_shell_history_list(shell_info_t *shell_info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (shell_info->history)
		node = shell_info->history;
	add_node_end(&node, buffer, line_count);

	if (!shell_info->history)
		shell_info->history = node;
	return 0;
}

/**
 * renumber_shell_history - renumbers the history linked list after changes
 * @shell_info: Structure containing potential arguments
 *
 * Return: the new history count
 */
int renumber_shell_history(shell_info_t *shell_info)
{
	list_t *node = shell_info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return shell_info->history_count = i;
}


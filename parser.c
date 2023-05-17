#include "shell.h"

/**
 * check_executable - determines if a file is an executable command
 * @info_struct: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int check_executable(info_t *info_struct, char *file_path)
{
	struct stat file_stats;

	(void)info_struct;
	if (!file_path || stat(file_path, &file_stats))
		return (0);

	if (file_stats.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - duplicates characters
 * @path_string: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_characters(char *path_string, int start_index, int stop_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < stop_index; i++)
		if (path_string[i] != ':')
			buffer[k++] = path_string[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_executable_path - finds this command in the PATH string
 * @info_struct: the info struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_executable_path(info_t *info_struct, char *path_string, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (check_executable(info_struct, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = duplicate_characters(path_string, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (check_executable(info_struct, path))
				return (path);
			if (!path_string[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

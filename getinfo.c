#include "shell.h"

/**
 * clear_shell_info - initializes shell_info_t struct
 * @shell_info: struct address
 */
void clear_shell_info(shell_info_t *shell_info)
{
	shell_info->arguments = NULL;
	shell_info->argument_vector = NULL;
	shell_info->path = NULL;
	shell_info->argument_count = 0;
}

/**
 * set_shell_info - initializes shell_info_t struct
 * @shell_info: struct address
 * @argv: argument vector
 */
void set_shell_info(shell_info_t *shell_info, char **argv)
{
	int i = 0;

	shell_info->program_name = argv[0];
	if (shell_info->arguments)
	{
		shell_info->argument_vector = strtow(shell_info->arguments, " \t");
		if (!shell_info->argument_vector)
		{
			shell_info->argument_vector = malloc(sizeof(char *) * 2);
			if (shell_info->argument_vector)
			{
				shell_info->argument_vector[0] = _strdup(shell_info->arguments);
				shell_info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; shell_info->argument_vector && shell_info->argument_vector[i]; i++)
			;
		shell_info->argument_count = i;

		replace_alias(shell_info);
		replace_variables(shell_info);
	}
}

/**
 * free_shell_info - frees shell_info_t struct fields
 * @shell_info: struct address
 * @all: true if freeing all fields
 */
void free_shell_info(shell_info_t *shell_info, int all)
{
	ffree(shell_info->argument_vector);
	shell_info->argument_vector = NULL;
	shell_info->path = NULL;
	if (all)
	{
		if (!shell_info->command_buffer)
			free(shell_info->arguments);
		if (shell_info->environment)
			free_list(&(shell_info->environment));
		if (shell_info->history)
			free_list(&(shell_info->history));
		if (shell_info->aliases)
			free_list(&(shell_info->aliases));
		ffree(shell_info->environment_copy);
		shell_info->environment_copy = NULL;
		bfree((void **)shell_info->command_buffer);
		if (shell_info->read_file_descriptor > 2)
			close(shell_info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}


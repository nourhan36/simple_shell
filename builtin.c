#include "shell.h"

/**
 * _custom_exit - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if data->args[0] != "exit"
 */
int _custom_exit(info_t *data)
{
	int exit_code_check;

	if (data->args[1]) /* If there is an exit argument */
	{
		exit_code_check = _custom_atoi(data->args[1]);
		if (exit_code_check == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_custom_puts(data->args[1]);
			_custom_putchar('\n');
			return (1);
		}
		data->err_code = _custom_atoi(data->args[1]);
		return (-2);
	}
	data->err_code = -1;
	return (-2);
}

/**
 * _custom_cd - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _custom_cd(info_t *data)
{
	char *str, *directory, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		_custom_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->args[1])
	{
		directory = _custom_getenv(data, "HOME=");
		if (!directory)
			chdir_ret = /* TODO: what should this be? */
				chdir((directory = _custom_getenv(data, "PWD=")) ? directory : "/");
		else
			chdir_ret = chdir(directory);
	}
	else if (_custom_strcmp(data->args[1], "-") == 0)
	{
		if (!_custom_getenv(data, "OLDPWD="))
		{
			_custom_puts(str);
			_custom_putchar('\n');
			return (1);
		}
		_custom_puts(_custom_getenv(data, "OLDPWD=")), _custom_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((directory = _custom_getenv(data, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_ret = chdir(data->args[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		_custom_eputs(data->args[1]), _custom_eputchar('\n');
	}
	else
	{
		_custom_setenv(data, "OLDPWD", _custom_getenv(data, "PWD="));
		_custom_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _custom_help - displays help information
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _custom_help(info_t *data)
{
	char **arg_array;

	arg_array = data->args;
	_custom_puts("help call works. Function not yet implemented \n");
	if (0)
		_custom_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}


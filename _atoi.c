#include "shell.h"

/**
 * is_mode_active - returns true if the shell is in an active mode
 * @data: struct address
 *
 * Return: 1 if active mode, 0 otherwise
 */
int is_mode_active(info_t *data)
{
	return (isatty(STDIN_FILENO) && data->fd_read <= 2);
}

/**
 * is_separator - checks if a character is a separator
 * @ch: the character to check
 * @sep: the separator string
 * Return: 1 if true, 0 if false
 */
int is_separator(char ch, char *sep)
{
	while (*sep)
		if (*sep++ == ch)
			return (1);
	return (0);
}

/**
 * is_alpha_char - checks for an alphabetic character
 * @ch: The character to check
 * Return: 1 if ch is alphabetic, 0 otherwise
 */
int is_alpha_char(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int convert_to_int(char *str)
{
	int i, sign = 1, flag = 0, result;
	unsigned int output = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			output *= 10;
			output += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -output;
	else
		result = output;

	return (result);
}

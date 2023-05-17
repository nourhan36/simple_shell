#include "shell.h"

/**
 * _custom_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _custom_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * custom_print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void custom_print_error(info_t *info, char *estr)
{
	_custom_print(info->fname);
	_custom_print(": ");
	custom_print_d(info->line_count, STDERR_FILENO);
	_custom_print(": ");
	_custom_print(info->argv[0]);
	_custom_print(": ");
	_custom_print(estr);
}

/**
 * custom_print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int custom_print_d(int input, int fd)
{
	int (*custom_putchar)(char) = custom_putchar;
	int i, count = 0;
	unsigned int abs_val, current;

	if (fd == STDERR_FILENO)
		custom_putchar = custom_eputchar;
	if (input < 0)
	{
		abs_val = -input;
		custom_putchar('-');
		count++;
	}
	else
		abs_val = input;
	current = abs_val;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_val / i)
		{
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	custom_putchar('0' + current);
	count++;

	return (count);
}

/**
 * custom_convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *custom_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * custom_remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void custom_remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}


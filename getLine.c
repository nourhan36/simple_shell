#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t lengthStored = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleSIGINT);
#if USE_GETLINE
		bytesRead = getline(buffer, &lengthStored, stdin);
#else
		bytesRead = custom_getline(info, buffer, &lengthStored);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0'; /* remove trailing newline */
				bytesRead--;
			}
			info->lineCountFlag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->historyCount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*length = bytesRead;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (bytesRead);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t iterator, j, length;
	ssize_t bytesRead = 0;
	char **bufferPointer = &(info->arg), *pointer;

	_putchar(FLUSH_BUFFER);
	bytesRead = buffer_input(info, &buffer, &length);
	if (bytesRead == -1) /* EOF */
		return (-1);
	if (length) /* we have commands left in the chain buffer */
	{
		j = iterator; /* init new iterator to current buffer position */
		pointer = buffer + iterator; /* get pointer for return */

		check_chain(info, buffer, &j, iterator, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		iterator = j + 1; /* increment past nulled ';'' */
		if (iterator >= length) /* reached end of buffer? */
		{
			iterator = length = 0; /* reset position and length */
			info->cmd_buffer_type = CMD_NORMAL;
		}

		*bufferPointer = pointer; /* pass back pointer to current command position */
		return (_strlen(pointer)); /* return length of current command */
	}

	*bufferPointer = buffer; /* else not a chain, pass back buffer from custom_getline() */
	return (bytesRead); /* return length of buffer from custom_getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @iterator: size
 *
 * Return: bytesRead
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *iterator)
{
	ssize_t bytesRead = 0;

	if (*iterator)
		return (0);
	bytesRead = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (bytesRead >= 0)
		*iterator = bytesRead;
	return (bytesRead);
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bytesRead
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t iterator, len;
	size_t k;
	ssize_t bytesRead = 0, bytesReadTotal = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		bytesReadTotal = *length;
	if (iterator == len)
		iterator = len = 0;

	bytesRead = read_buffer(info, buffer, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return (-1);

	c = _custom_strchr(buffer + iterator, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _custom_realloc(p, bytesReadTotal, bytesReadTotal ? bytesReadTotal + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (bytesReadTotal)
		_custom_strncat(new_p, buffer + iterator, k - iterator);
	else
		_custom_strncpy(new_p, buffer + iterator, k - iterator + 1);

	bytesReadTotal += k - iterator;
	iterator = k;
	p = new_p;

	if (length)
		*length = bytesReadTotal;
	*ptr = p;
	return (bytesReadTotal);
}

/**
 * handleSIGINT - blocks ctrl-C
 * @signalNumber: the signal number
 *
 * Return: void
 */
void handleSIGINT(__attribute__((unused))int signalNumber)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}


#include "shell.h"

/**
 * custom_memset - fills memory with a constant byte
 * @mem: the pointer to the memory area
 * @val: the byte to fill *mem with
 * @size: the amount of bytes to be filled
 * Return: (mem) a pointer to the memory area mem
 */
char *custom_memset(char *mem, char val, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		mem[i] = val;
	return (mem);
}

/**
 * free_string_array - frees a string array
 * @str_arr: string array
 */
void free_string_array(char **str_arr)
{
	char **ptr = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(ptr);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}

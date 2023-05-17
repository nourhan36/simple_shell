#include "shell.h"

/**
 * split_string - splits a string into words. Repeat delimiters are ignored
 * @input_string: the input string
 * @delimiters: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string(char *input_string, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **result;

	if (input_string == NULL || input_string[0] == 0)
		return (NULL);

	if (!delimiters)
		delimiters = " ";

	for (i = 0; input_string[i] != '\0'; i++)
		if (!is_delimiter(input_string[i], delimiters) && (is_delimiter(input_string[i + 1], delimiters) || !input_string[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);

	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(input_string[i], delimiters))
			i++;

		k = 0;
		while (!is_delimiter(input_string[i + k], delimiters) && input_string[i + k])
			k++;

		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			result[j][m] = input_string[i++];

		result[j][m] = 0;
	}

	result[j] = NULL;
	return (result);
}

/**
 * split_string2 - splits a string into words
 * @input_string: the input string
 * @delimiter: the delimiter character
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string2(char *input_string, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **result;

	if (input_string == NULL || input_string[0] == 0)
		return (NULL);

	for (i = 0; input_string[i] != '\0'; i++)
		if ((input_string[i] != delimiter && input_string[i + 1] == delimiter) ||
		    (input_string[i] != delimiter && !input_string[i + 1]) || input_string[i + 1] == delimiter)
			num_words++;

	if (num_words == 0)
		return (NULL);

	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (input_string[i] == delimiter && input_string[i] != delimiter)
			i++;

		k = 0;
		while (input_string[i + k] != delimiter && input_string[i + k] && input_string[i + k] != delimiter)
			k++;

		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			result[j][m] = input_string[i++];

		result[j][m] = 0;
	}

	result[j] = NULL;
	return (result);
}

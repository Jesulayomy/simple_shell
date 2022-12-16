#include "shell.h"

/**
 * get_commands - gets a command
 * @buffer: a buffer
 * @n: size of buffer
 *
 * Return: an array of split tokens of commands
 */
char **get_commands(char *buffer, size_t n)
{
	char **arr = NULL;
	char *token;
	size_t k = 0;
	ssize_t i, r;

	r = my_getline(&buffer, &n, stdin);
	if (r == -1)
	{
		free(buffer);
		return (arr);
	}

	for (i = 0; i < r; i++)
	{
		if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t')
		{
			k++;
		}
		else
			continue;
	}

	arr = malloc(sizeof(char *) * (k + 1));
	token = my_strtok(buffer, DELIM_T);
	i = 0;
	while (token != NULL)
	{
		arr[i] = malloc(sizeof(char) * (my_strlen(token) + 1));
		my_strcpy(arr[i], token);
		token = my_strtok(NULL, DELIM_T);
		i++;
	}
	arr[i] = NULL;

	free(buffer);
	return (arr);
}

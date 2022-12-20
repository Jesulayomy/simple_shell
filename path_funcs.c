#include "shell.h"

/**
 * add_node_end - adds a new node at the end of the path_l linked list
 * @head: pointer to the list
 * @str: string to add to the end of the list
 *
 * Return: address of new list
 */
path_l *add_node_end(path_l **head, char *str)
{
	path_l *list, *temp;

	temp = *head;
	list = malloc(sizeof(path_l));

	if (!list)
		return (NULL);

	list->str = my_strdup(str);
	list->next = NULL;

	if (!temp)
	{
		*head = list;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = list;
	}

	return (*head);
}

/**
 * path_to_list - creates a linked list of each directory contained in the PATH
 * environment variable
 * @environ: the environment
 *
 * Return: a linked list containing the PATH's paths
 */
path_l *path_to_list(sh_data *shell)
{
	char path[5] = "PATH";
	int i, j, k, check;
	path_l *head = NULL;
	char *str;

	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && path[j] != '\0')
		{
			if (shell->_environ[i][j] != path[j])
				check = 1;
			j++;
		} k = 0;
		if (check == 0)
		{
			j++;
			while (shell->_environ[i][j])
			{
				if (shell->_environ[i][j] == ':')
				{
					str[k] = '\0', k = 0;
					add_node_end(&head, str);
					free(str);

				}
				else
				{
					if (k == 0)
						str = malloc(sizeof(char) * 150);
					str[k] = shell->_environ[i][j], k++;
				} j++;
			}
			str[k] = '\0';
			add_node_end(&head, str);
			free(str);
			break;
		}
	}
	str = _getenv(shell, "PWD");
	add_node_end(&head, str);
	free(str);

	return (head);
}

/**
 * search_path - searches a path linked list to find a particular file
 * @list: pointer to a path list
 * @file: file to search for
 *
 * Return: pointer to full path name of NULL if not found
 */
char *search_path(path_l *list, char *file)
{
	path_l *temp = list;
	char *path;
	struct stat s;

	while (temp)
	{
		path = malloc(sizeof(char) * (my_strlen(temp->str) + my_strlen(file) + 2));

		if (file[0] == '/')
		{
			free(path);
			path = my_strdup(file);
			return (path);
		}

		my_strcpy(path, temp->str);
		my_strcat(path, "/");
		my_strcat(path, file);
		if (stat(path, &s) == 0)
			return (path);

		free(path);
		temp = temp->next;
	}

	return (NULL);
}

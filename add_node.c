#include "shell.h"

/**
 * add_node_end - adds a new node at the end of the list_t list
 * @head: pointer to list
 * @str: string to add
 *
 * Return: address of new list
 */
path_l *add_node_end(path_l **head, const char *str)
{
	path_l *list, *temp;

	temp = *head;
	list = malloc(sizeof(path_l));

	if (!list)
		return (NULL);

	list->str = strdup(str);
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

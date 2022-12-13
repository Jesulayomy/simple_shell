#include "main.h"

/**
 * print_list - prints a list
 * @h: the list
 *
 * Return: number of nodes
 */
size_t print_list(const path_l *h)
{
	const path_l *list = h;
	size_t count = 0;

	while (list)
	{
		if (list->str)
			printf("%s\n", list->str);
		else
			printf("[0] (nil)\n");
		count++;
		list = list->next;
	}

	return (count);
}

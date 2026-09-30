#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_list.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

/* usage: ./a.out <data to remove> [list elements...] */
int	main(int ac, char **av)
{
	t_list	*list;
	t_list	*node;
	int		i;

	if (ac < 2)
		return (0);
	list = NULL;
	i = ac - 1;
	while (i >= 2)
	{
		node = malloc(sizeof(t_list));
		node->data = av[i];
		node->next = list;
		list = node;
		i--;
	}
	ft_list_remove_if(&list, av[1], &strcmp);
	printf("list:");
	node = list;
	while (node)
	{
		printf(" [%s]", (char *)node->data);
		node = node->next;
	}
	printf("\n");
	while (list)
	{
		node = list->next;
		free(list);
		list = node;
	}
	return (0);
}

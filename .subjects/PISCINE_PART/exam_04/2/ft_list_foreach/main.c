#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *));

static int	g_calls = 0;

static void	print_data(void *data)
{
	printf("[%s]", (char *)data);
	g_calls++;
}

static void	upper_first(void *data)
{
	char	*s;

	s = (char *)data;
	if (*s >= 'a' && *s <= 'z')
		*s -= 32;
}

/* builds a list from the arguments, then applies two functions to it */
int	main(int ac, char **av)
{
	t_list	*list;
	t_list	*node;
	int		i;

	list = NULL;
	i = ac - 1;
	while (i >= 1)
	{
		node = malloc(sizeof(t_list));
		node->data = av[i];
		node->next = list;
		list = node;
		i--;
	}
	ft_list_foreach(list, &upper_first);
	ft_list_foreach(list, &print_data);
	printf("\n%d calls\n", g_calls);
	while (list)
	{
		node = list->next;
		free(list);
		list = node;
	}
	return (0);
}

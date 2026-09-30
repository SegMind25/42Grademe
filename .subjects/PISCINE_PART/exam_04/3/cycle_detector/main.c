#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int	cycle_detector(const t_list *list);

/* usage: ./a.out <nb nodes> <index the last node points to, -1 for none> */
int	main(int ac, char **av)
{
	t_list	nodes[1000];
	int		n;
	int		loop;
	int		i;

	if (ac != 3)
		return (0);
	n = atoi(av[1]);
	loop = atoi(av[2]);
	if (n < 0 || n > 1000 || loop >= n)
		return (0);
	for (i = 0; i < n; i++)
	{
		nodes[i].data = i;
		nodes[i].next = (i + 1 < n) ? &nodes[i + 1] : NULL;
	}
	if (n > 0 && loop >= 0)
		nodes[n - 1].next = &nodes[loop];
	printf("%d\n", cycle_detector(n > 0 ? &nodes[0] : NULL));
	return (0);
}

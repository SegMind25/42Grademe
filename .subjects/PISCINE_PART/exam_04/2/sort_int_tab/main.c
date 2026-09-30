#include <stdio.h>
#include <stdlib.h>

void	sort_int_tab(int *tab, unsigned int size);

int	main(int ac, char **av)
{
	int	tab[64];
	int	i;

	if (ac < 2 || ac > 65)
		return (0);
	for (i = 1; i < ac; i++)
		tab[i - 1] = atoi(av[i]);
	sort_int_tab(tab, ac - 1);
	for (i = 0; i < ac - 1; i++)
		printf("%d%s", tab[i], i < ac - 2 ? " " : "\n");
	return (0);
}

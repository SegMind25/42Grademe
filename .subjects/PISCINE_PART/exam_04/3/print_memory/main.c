#include <stdlib.h>
#include <string.h>

void	print_memory(const void *addr, size_t size);

/* usage: ./a.out <test number> */
int	main(int ac, char **av)
{
	int				tab[10] = {0, 23, 150, 255, 12, 16, 21, 42};
	unsigned char	all[256];
	char			*str;
	int				i;

	if (ac != 2)
		return (0);
	str = "Hello, 42 world!\n\tThis is ~print_memory~ :)";
	i = 0;
	while (i < 256)
	{
		all[i] = (unsigned char)i;
		i++;
	}
	if (atoi(av[1]) == 1)
		print_memory(tab, sizeof(tab));
	else if (atoi(av[1]) == 2)
		print_memory(str, strlen(str) + 1);
	else if (atoi(av[1]) == 3)
		print_memory(all, sizeof(all));
	else if (atoi(av[1]) == 4)
		print_memory(all + 65, 3);
	else if (atoi(av[1]) == 5)
		print_memory(all + 120, 17);
	else if (atoi(av[1]) == 6)
		print_memory(all, 0);
	return (0);
}

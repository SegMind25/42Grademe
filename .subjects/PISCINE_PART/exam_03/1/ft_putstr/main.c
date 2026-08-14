#include <unistd.h>

void ft_putstr(char *str);

int main(int ac, char **av)
{
	if (ac == 2)
		ft_putstr(av[1]);
	write(1, "\n", 1);
	return (0);
}

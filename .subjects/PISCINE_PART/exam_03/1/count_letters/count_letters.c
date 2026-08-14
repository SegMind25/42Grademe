#include <unistd.h>
void ft_putnbr(int nb)
{
	char c;

	if (nb >= 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

int main(int ac, char **av)
{
	int i = 0;
	int count = 0;

	if (ac == 2 && av[1][0])
	{
		while (av[1][i])
		{
			if ((av[1][i] >= 'a' && av[1][i] <= 'z')
				|| (av[1][i] >= 'A' && av[1][i] <= 'Z'))
				count++;
			i++;
		}
		ft_putnbr(count);
	}
	write(1, "\n", 1);
	return (0);
}

#include <unistd.h>
void ft_putnbr(int nb)
{
	char c;

	if (nb >= 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

void pingpong(int n)
{
	if (n % 15 == 0)
		write(1, "pingpong\n", 9);
	else if (n % 3 == 0)
		write(1, "ping\n", 5);
	else if (n % 5 == 0)
		write(1, "pong\n", 5);
	else
	{
		ft_putnbr(n);
		write(1, "\n", 1);
	}
}

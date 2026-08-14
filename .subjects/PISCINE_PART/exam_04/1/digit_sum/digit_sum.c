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
	int sum = 0;
	int tmp;

	if (ac == 2)
	{
		while (av[1][i])
		{
			sum += av[1][i] - '0';
			i++;
		}
		while (sum >= 10)
		{
			tmp = 0;
			while (sum)
			{
				tmp += sum % 10;
				sum /= 10;
			}
			sum = tmp;
		}
		ft_putnbr(sum);
	}
	write(1, "\n", 1);
	return (0);
}

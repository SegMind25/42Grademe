#include <unistd.h>
void ft_hex(unsigned int n)
{
	char *base = "0123456789ABCDEF";

	if (n >= 16)
		ft_hex(n / 16);
	write(1, &base[n % 16], 1);
}

int main(int ac, char **av)
{
	int i = 0;
	unsigned int n = 0;

	if (ac == 2)
	{
		while (av[1][i])
		{
			n = n * 10 + (av[1][i] - '0');
			i++;
		}
		ft_hex(n);
	}
	write(1, "\n", 1);
	return (0);
}

#include <unistd.h>
void ft_putnbr(int nb)
{
	char c;

	if (nb >= 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

char ft_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int main(int ac, char **av)
{
	int i = 0;
	int j;
	int seen;
	int count;
	int first = 1;

	if (ac == 2 && av[1][0])
	{
		while (av[1][i])
		{
			char c = ft_lower(av[1][i]);

			if (c >= 'a' && c <= 'z')
			{
				seen = 0;
				j = 0;
				while (j < i)
				{
					if (ft_lower(av[1][j]) == c)
						seen = 1;
					j++;
				}
				if (!seen)
				{
					count = 0;
					j = i;
					while (av[1][j])
					{
						if (ft_lower(av[1][j]) == c)
							count++;
						j++;
					}
					if (!first)
						write(1, ", ", 2);
					ft_putnbr(count);
					write(1, &c, 1);
					first = 0;
				}
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}

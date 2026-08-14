#include <unistd.h>
int main(int ac, char **av)
{
	int len = 0;
	int i = 0;

	if (ac == 2)
	{
		while (av[1][len])
			len++;
		while (i < len / 2)
		{
			if (av[1][i] != av[1][len - 1 - i])
			{
				write(1, "\n", 1);
				return (0);
			}
			i++;
		}
		write(1, av[1], len);
		write(1, "\n", 1);
		return (0);
	}
	write(1, "\n", 1);
	return (0);
}

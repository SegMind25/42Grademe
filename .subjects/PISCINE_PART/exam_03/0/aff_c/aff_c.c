#include <unistd.h>
int main(int ac, char **av)
{
	int i = 0;

	if (ac == 2)
	{
		while (av[1][i])
		{
			if (av[1][i] == 'c')
			{
				write(1, "c\n", 2);
				return (0);
			}
			i++;
		}
	}
	write(1, "c\n", 2);
	return (0);
}

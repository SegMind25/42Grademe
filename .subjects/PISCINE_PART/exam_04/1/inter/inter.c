#include <unistd.h>
int main(int ac, char **av)
{
	int i = 0;
	int j;
	int k;
	int seen;

	if (ac == 3)
	{
		while (av[1][i])
		{
			seen = 0;
			j = 0;
			while (av[2][j])
			{
				if (av[1][i] == av[2][j])
					seen = 1;
				j++;
			}
			k = 0;
			while (k < i)
			{
				if (av[1][i] == av[1][k])
					seen = 0;
				k++;
			}
			if (seen)
				write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}

#include <unistd.h>
int main(int ac, char **av)
{
	int i = 0;

	if (ac == 2 && av[1][0])
	{
		while (av[1][i])
		{
			int count = 1;
			char c;

			while (av[1][i + 1] == av[1][i])
			{
				count++;
				i++;
			}
			if (count > 1)
			{
				c = count + '0';
				write(1, &c, 1);
			}
			write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}

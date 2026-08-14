#include <unistd.h>
int main(int ac, char **av)
{
	int len = 0;

	if (ac == 2)
	{
		while (av[1][len])
			len++;
		if (len == 0)
		{
			write(1, "\n", 1);
			return (0);
		}
		write(1, &av[1][0], 1);
		write(1, &av[1][len - 1], 1);
		write(1, "\n", 1);
		return (0);
	}
	write(1, "\n", 1);
	return (0);
}

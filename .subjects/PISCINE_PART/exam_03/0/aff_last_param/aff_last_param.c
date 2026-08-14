#include <unistd.h>
int main(int ac, char **av)
{
	int i = 0;
	char *last;

	if (ac >= 2)
	{
		last = av[ac - 1];
		while (last[i])
		{
			write(1, &last[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}

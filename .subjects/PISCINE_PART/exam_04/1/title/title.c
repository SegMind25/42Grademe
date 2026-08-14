#include <unistd.h>
int main(int ac, char **av)
{
	int i = 0;
	int new_word = 1;

	if (ac == 2)
	{
		while (av[1][i])
		{
			if (av[1][i] >= 'a' && av[1][i] <= 'z' && new_word)
			{
				char c = av[1][i] - 32;

				write(1, &c, 1);
			}
			else
				write(1, &av[1][i], 1);
			new_word = (av[1][i] == ' ');
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}

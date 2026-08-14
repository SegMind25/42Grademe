#include <unistd.h>

void write_string(char *str);

int main(int ac, char **av)
{
	if (ac == 2)
		write_string(av[1]);
	write(1, "\n", 1);
	return (0);
}

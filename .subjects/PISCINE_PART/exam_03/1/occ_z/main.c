#include <stdio.h>

int occ_z(char *str);

int main(int ac, char **av)
{
	if (ac == 2)
		printf("%d\n", occ_z(av[1]));
	else
		printf("\n");
	return (0);
}

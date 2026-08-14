#include <stdio.h>

int count_len(char *str);

int main(int ac, char **av)
{
	if (ac == 2)
		printf("%d\n", count_len(av[1]));
	else
		printf("\n");
	return (0);
}

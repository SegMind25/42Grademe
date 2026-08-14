#include <stdio.h>

int sum_digits(char *str);

int main(int ac, char **av)
{
	if (ac == 2)
		printf("%d\n", sum_digits(av[1]));
	else
		printf("\n");
	return (0);
}

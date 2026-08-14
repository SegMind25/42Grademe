#include <stdio.h>

int ft_strlen(char *str);

int main(int ac, char **av)
{
	if (ac == 2)
		printf("%d\n", ft_strlen(av[1]));
	else
		printf("\n");
	return (0);
}

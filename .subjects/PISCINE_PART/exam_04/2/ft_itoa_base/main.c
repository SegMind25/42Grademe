#include <stdio.h>
#include <stdlib.h>

char	*ft_itoa_base(int value, int base);

int	main(int ac, char **av)
{
	char	*s;

	if (ac != 3)
		return (0);
	s = ft_itoa_base(atoi(av[1]), atoi(av[2]));
	printf("%s\n", s ? s : "(null)");
	free(s);
	return (0);
}

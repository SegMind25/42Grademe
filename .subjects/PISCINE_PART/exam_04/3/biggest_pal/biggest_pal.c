#include <unistd.h>

/* reference: longest palindrome, the last one when several have that length */

static int	is_pal(char *s, int start, int len)
{
	int	i;

	i = 0;
	while (i < len / 2)
	{
		if (s[start + i] != s[start + len - 1 - i])
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	n;
	int	len;
	int	start;

	if (ac == 2)
	{
		n = 0;
		while (av[1][n])
			n++;
		len = n;
		while (len > 0)
		{
			start = n - len;
			while (start >= 0)
			{
				if (is_pal(av[1], start, len))
				{
					write(1, av[1] + start, len);
					write(1, "\n", 1);
					return (0);
				}
				start--;
			}
			len--;
		}
	}
	write(1, "\n", 1);
	return (0);
}

#include <unistd.h>
#include <stdlib.h>

static int ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

static int ft_strstr(char *hay, char *needle, int sublen)
{
	int i = 0;
	int j;

	while (hay[i])
	{
		j = 0;
		while (j < sublen && hay[i + j] && hay[i + j] == needle[j])
			j++;
		if (j == sublen)
			return (1);
		i++;
	}
	return (0);
}

static int all_contain(char **av, int ac, char *sub, int sublen)
{
	int i = 1;

	while (i < ac)
	{
		if (!ft_strstr(av[i], sub, sublen))
			return (0);
		i++;
	}
	return (1);
}

int main(int ac, char **av)
{
	int i;
	int j;
	int len;
	int bestlen = 0;
	int beststart = 0;

	if (ac >= 2)
	{
		len = ft_strlen(av[1]);
		i = 0;
		while (i < len)
		{
			j = i;
			while (j < len)
			{
				if (all_contain(av, ac, av[1] + i, j - i + 1))
				{
					if (j - i + 1 > bestlen)
					{
						bestlen = j - i + 1;
						beststart = i;
					}
				}
				j++;
			}
			i++;
		}
		write(1, av[1] + beststart, bestlen);
	}
	write(1, "\n", 1);
	return (0);
}

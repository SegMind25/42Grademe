#include <unistd.h>
char *rev_print(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	while (i > 0)
	{
		i--;
		write(1, &str[i], 1);
	}
	return (str);
}

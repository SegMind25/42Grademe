#include <unistd.h>
void print_nth_char(char *str, int n)
{
	int i = 1;
	int len = 0;

	while (str[len])
		len++;
	if (n <= 0 || len == 0 || n > len)
	{
		write(1, "\n", 1);
		return;
	}
	while (i <= len)
	{
		if (i % n == 0)
			write(1, &str[i - 1], 1);
		i++;
	}
	write(1, "\n", 1);
}

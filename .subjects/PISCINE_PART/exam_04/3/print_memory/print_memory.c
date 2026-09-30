#include <unistd.h>

/* reference: 16 bytes per line, hex by pairs of bytes, then printable chars */

static void	put_hex(unsigned char c)
{
	char	*hex;

	hex = "0123456789abcdef";
	write(1, &hex[c / 16], 1);
	write(1, &hex[c % 16], 1);
}

void	print_memory(const void *addr, size_t size)
{
	const unsigned char	*p;
	size_t				line;
	size_t				i;

	p = (const unsigned char *)addr;
	line = 0;
	while (line < size)
	{
		i = 0;
		while (i < 16)
		{
			if (line + i < size)
				put_hex(p[line + i]);
			else
				write(1, "  ", 2);
			if (i % 2 == 1)
				write(1, " ", 1);
			i++;
		}
		i = 0;
		while (i < 16 && line + i < size)
		{
			if (p[line + i] >= 32 && p[line + i] <= 126)
				write(1, &p[line + i], 1);
			else
				write(1, ".", 1);
			i++;
		}
		write(1, "\n", 1);
		line += 16;
	}
}

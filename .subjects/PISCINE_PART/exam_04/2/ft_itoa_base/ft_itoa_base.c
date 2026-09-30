#include <stdlib.h>

/* reference: base 10 keeps the sign, other bases read the value as unsigned */

char	*ft_itoa_base(int value, int base)
{
	char			*digits;
	char			buf[34];
	char			*res;
	unsigned int	n;
	int				neg;
	int				i;
	int				len;

	digits = "0123456789ABCDEF";
	if (base < 2 || base > 16)
		return (NULL);
	neg = (base == 10 && value < 0);
	n = neg ? -(unsigned int)value : (unsigned int)value;
	i = 33;
	buf[i] = '\0';
	if (n == 0)
		buf[--i] = '0';
	while (n > 0)
	{
		buf[--i] = digits[n % base];
		n /= base;
	}
	if (neg)
		buf[--i] = '-';
	len = 33 - i;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len-- > 0)
		res[len] = buf[i + len];
	return (res);
}

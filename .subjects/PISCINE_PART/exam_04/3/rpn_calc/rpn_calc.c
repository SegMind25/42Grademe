#include <stdio.h>
#include <stdlib.h>

/* reference: evaluate a Reverse Polish Notation expression */

static int	is_op(char *s)
{
	return ((*s == '+' || *s == '-' || *s == '*' || *s == '/' || *s == '%')
		&& (s[1] == ' ' || s[1] == '\0'));
}

static int	rpn(char *s, long *result)
{
	long	stack[4096];
	int		top;
	long	a;
	long	b;
	int		i;

	top = 0;
	while (*s)
	{
		if (*s == ' ')
		{
			s++;
			continue ;
		}
		if (is_op(s))
		{
			if (top < 2)
				return (0);
			b = stack[--top];
			a = stack[--top];
			if ((*s == '/' || *s == '%') && b == 0)
				return (0);
			if (*s == '+')
				stack[top++] = a + b;
			else if (*s == '-')
				stack[top++] = a - b;
			else if (*s == '*')
				stack[top++] = a * b;
			else if (*s == '/')
				stack[top++] = a / b;
			else
				stack[top++] = a % b;
			s++;
			continue ;
		}
		i = (*s == '-') ? 1 : 0;
		if (s[i] < '0' || s[i] > '9')
			return (0);
		while (s[i] >= '0' && s[i] <= '9')
			i++;
		if (s[i] != ' ' && s[i] != '\0')
			return (0);
		if (top >= 4096)
			return (0);
		stack[top++] = atoi(s);
		s += i;
	}
	if (top != 1)
		return (0);
	*result = stack[0];
	return (1);
}

int	main(int ac, char **av)
{
	long	result;

	if (ac == 2 && rpn(av[1], &result))
		printf("%ld\n", result);
	else
		printf("Error\n");
	return (0);
}

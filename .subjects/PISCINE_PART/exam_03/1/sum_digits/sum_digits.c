int sum_digits(char *str)
{
	int i = 0;
	int sum = 0;

	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			sum += str[i] - '0';
		i++;
	}
	return (sum);
}

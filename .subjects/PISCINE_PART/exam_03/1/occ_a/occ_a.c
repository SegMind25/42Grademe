int occ_a(char *str)
{
	int i = 0;
	int count = 0;

	while (str[i])
	{
		if (str[i] == 'A')
			count++;
		i++;
	}
	return (count);
}

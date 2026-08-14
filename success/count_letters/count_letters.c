#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c)
{
  write(1, &c , 1);
}

void ft_putnbr(int nb)
{
  if(nb >= 10)
  {
    ft_putnbr(nb / 10);
  }
  ft_putchar(nb % 10 + '0');
}

int ft_strlen(char *str)
{
  int len = 0;
  int count = 0;
  while(str[len])
  {
    if((str[len] >= 'a' && str[len] <= 'z') || (str[len] >= 'A' && str[len] <= 'Z' ))
    {
      count = count + 1;
    }
    len++;
  }
  return count;
}

int main(int ac, char **av)
{

  if(ac == 2)
  {
    ft_putnbr(ft_strlen(av[1]));
  }
  return 0;
}

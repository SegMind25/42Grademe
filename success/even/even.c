#include <unistd.h>

void ft_putchar(char c)
{
  write(1, &c ,1);
}

int ft_putnbr(int nb)
{
  if(nb == 10)
  {
    ft_putnbr(nb / 10);
  }
  ft_putchar(nb % 10 + '0');
}

void ft_is_even(void)
{
  int i = 0;
  while(i >= 0 && i <= 10)
  {
    if(i % 2 == 0)
      ft_putnbr(i);
    i++;
  }
  write(1, "\n", 1);
}


int main(int ac, char **av)
{

  if(ac == 1)
  {
    (void)av;
    ft_is_even();
  }
  return 0;
}

#include <unistd.h>

void ft_putchar(char c)
{
  write(1, &c, 1);
}

void ft_putstr(char *str)
{
  while(*str)
  {
    write(1, str++, 1);
  }
}

int main()
{

  ft_putchar('h');
  ft_putstr("\n");

  return 0;
}

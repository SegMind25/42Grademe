#include <unistd.h>

void ft_putchar(char c)
{
  write(1, &c, 1);
}

int main()
{

  ft_putchar('d');
  ft_putchar('\n');

  return 0;
}

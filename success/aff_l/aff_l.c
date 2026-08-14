#include <unistd.h>

int main(int ac, char **av)
{

  (void)ac;
  (void)av;
  write(1, "l\n", 2);

  return 0;
}

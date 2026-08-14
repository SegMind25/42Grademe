#include <unistd.h>

int main(int ac, char **av)
{

  (void)ac;
  (void)av;
  write(1, "n\n", 1);

  return 0;
}

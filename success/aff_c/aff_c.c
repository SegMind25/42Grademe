#include <unistd.h>

int main(int ac, char **av)
{

  int iye;

  if(ac == 1)
  {
    write(1, "c\n", 2);
  }

  if(ac == 2)
  {
    iye = 0;
    while(av[1][iye])
    {
      if(av[1][iye] == 'c')
      {
        write(1, "c\n", 2);
        return 0;
      }
      iye++;
    }
  }

  return 0;
}

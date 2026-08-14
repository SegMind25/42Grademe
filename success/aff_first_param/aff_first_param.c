#include <unistd.h>

int main(int ac, char **av)
{

  int ayo;
  if(ac >= 2)
  {
    ayo = 0;
    while(av[1][ayo] && (av[1][ayo] == ' ' || av[1][ayo] == '\t'))
    {
      ayo++;
    }
    while(av[1][ayo] && (av[1][ayo] != ' ' && av[1][ayo] != '\t'))
    {
      write(1, &av[1][ayo], 1);
      ayo++;
    }
  }
  write(1, "\n", 1);
  return 0;
}

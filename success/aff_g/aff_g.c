#include <unistd.h>

int main(int ac, char **av)
{

  int ayo;
  int chill;
  if(ac == 2)
  {
    ayo = 1;
    chill = 0;
    
    while(av[ayo][chill])
    {
      if(av[ayo][chill] == 'g')
      {
        write(1, "g\n", 2);
        return 0;
      }
      chill++;
    }
    write(1, "g\n", 1);
  }
  return 0;
}

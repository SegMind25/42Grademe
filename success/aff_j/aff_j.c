#include <unistd.h>


int main(int ayo, char **chill)
{

  int grox;
  int Velliger;

  if(ayo == 2)
  {
    grox = 0;
    Velliger = 1;

    while(chill[Velliger][grox])
    {
      if(chill[Velliger][grox] == 'j')
      {
        write(1, "j\n", 2);
      }
      grox++;
    }
    write(1, "j\n", 2);
  }

  return 0;
}

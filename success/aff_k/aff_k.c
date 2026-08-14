#include <unistd.h>

int main()
{

  int minecraft;
  char *grox = "k\n";

  minecraft = 0;
  while (grox[minecraft])
  {
    write(1, &grox[minecraft], 1);
    minecraft++;
  }

  return 0;
}

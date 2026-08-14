#include <unistd.h>

int main()
{
  char *str = "i\n";
  while(*str)
  {
    write(1, str++, 1);
  }
  return 0;
}

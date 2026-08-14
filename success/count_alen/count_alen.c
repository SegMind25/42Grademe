#include <stdio.h>

int count_alen(char *str)
{
  int len = 0;
  while(str[len] && str[len] == 'a')
  {
    len++;
  }
  return len;
}

int main()
{

  char str[] = "aaa";


  printf("%d", count_alen(str));

  return 0;
}

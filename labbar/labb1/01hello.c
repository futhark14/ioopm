#include <stdio.h>

int main(void)
{
  // printf("Hello world!!!\n");
  puts("Hello, world!");
  // Skillnaden mellan dem är att den senare skriver en radbrytning på slutet

  char *msg = "Hello, world!";
  int year = 2020;
  printf("%s in the year %d\n", msg, year);

  return 0;
}
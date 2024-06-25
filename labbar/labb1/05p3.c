#include <stdio.h>

int main(void)
{
  int counter = 0;
  for(int i = 1; i <= 10; i++)
  {
    for(int j = 1; j <= i; j++)
    {
      printf("*");
      counter++;
    }
    printf("\n");
  }
  printf("TOtalt: %d\n",counter);
  return 0;
}
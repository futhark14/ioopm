#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
  int N = (atoi(argv[1]));
  printf("N=%d\n", N);

  int limit = floor(sqrt(N)) + 1;

  for(int i = 2; i <= limit; i++)
  {
    for(int j = 2; j <= i; j++)
    {
      if(N == i*j)
      {
        printf("N=%d is not a prime number, it is the product of %d * %d\n", N, i, j);
        return 0;
      }
    }
  }
  printf("N is a prime number\n");
  return 0;
}
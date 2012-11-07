#include <stdio.h>
#include <stdlib.h>

int fact(int n)
{
  if(n <= 1)
    return 1;
  else return n*fact(n - 1);
}

int main(int argc, char * argv[], char* env[])
{
  int n = 3;
  printf("%d\n", fact(n));
  return 0;
}

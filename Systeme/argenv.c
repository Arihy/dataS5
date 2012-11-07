#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[], char* env[])
{
  int nbParametre = argc;
  int k = 0;
  int nbVarEn = 0;
  printf("le nombre de parametre entree = %d\n",nbParametre - 1);
  for(int i = 1; i < argc; i++)
    {
      printf("parametre numero %d = %s\n", i, argv[i]);
    }
  while(env[k] != NULL)
    {
    nbVarEn++;
    printf("var env numero %d = %s\n", k+1, env[k]);
    k++;
  }
  printf("il y a %d variable d'environnement\n", nbVarEn);
  return 0;
}

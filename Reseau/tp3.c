//MOHAMED EL-HAD Mellany

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[], char* env[])
{
  int i = 0;
  struct hostent *strHostent = NULL;
  if(argc >= 2)
  {
    strHostent = gethostbyname(argv[1]); //recuperation de la struct hostent
  }
  
  char* addr = inet_ntoa( *((struct in_addr *) (strHostent->h_addr_list[0])));
  //for(int i = 0; i < strHostent->h_length; i++)
  printf("adresse ip: %s\n", addr);
  printf("nom officiel: %s\n", strHostent->h_name);
  
  while(strHostent->h_aliases[i] != NULL)
  {
    printf("alias %d: %s\n", i, strHostent->h_aliases[i]);
    i++;
  }
  printf("\n");
  
  printf("type des adresses = %d\n", strHostent->h_addrtype);
  printf("taille des adresses = %d\n", strHostent->h_length);
  printf("\n\n");
  printf("liste des adresses: \n");
  
  i = 0;
  while(strHostent->h_addr_list[i] != NULL)
  {
    printf("adresse ip %d: %s\n", i, inet_ntoa( *((struct in_addr *) (strHostent->h_addr_list[i]))));
    i++;
  }
  
return 0;
}

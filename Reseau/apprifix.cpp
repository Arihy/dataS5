/**MOHAMED EL-HAD Mellany
*APPRIFIX
*/


#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "sock.h"
#include "sockdist.h"
#include <arpa/inet.h>


using namespace std;

int main(int argc, char* argv[])
{
  Sock boite(SOCK_DGRAM, (short)33400, 0);
  int desc;
  if(boite.good()){
    desc = boite.getsDesc();
  }
  else{
    cout << "pb BR local" << endl;
    return 1;
  }
  
  char msg[100];
  char reception[100];
  
  SockDist boiteDistant;
  struct sockaddr_in *adrDist = boiteDistant.getAdrDist();
  socklen_t taille = boiteDistant.getsLen();

  cout << "Appuyer sur entre pour continuer";
  cin.getline(msg, 100);
  
  //int nbMessage = 0;
  
  cout << "Attente de message" << endl;
  
  //for(int i = 0; i < 10000; i++)
  //{
  while(true)
  {
    int retourRec = recvfrom(desc,reception,100, 0, (struct sockaddr *)adrDist, &taille);
    if(retourRec > 0)
    {
      cout << "Message reçu : " << reception << endl;
      break;
      //nbMessage++;
      //cout << nbMessage << endl;
    }
  }
  //}

  cout << "Taper un message : " << endl;
 
  cin.getline(msg, 100);
  
  int retourSend = sendto(desc, msg, 100, 0, (struct sockaddr *)adrDist, taille);

  if(retourSend <= 0)
  {
    cout << "message non envoyé" << endl;
  }

  close(desc);

  return 0; 
}

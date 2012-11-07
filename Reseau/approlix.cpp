//client
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
 
  Sock boite(SOCK_DGRAM, 0, 0);
  int desc;
  if(boite.good()){
    desc = boite.getsDesc();
  }
  else{
    cout << "pb BR local" << endl;
    return 1;
  }
  
  char msg[100] = "coucou";
  char reception[100];
  
  SockDist boiteDistant(argv[1], atoi(argv[2]));
  struct sockaddr_in *adrDist = boiteDistant.getAdrDist();
  int taille = sizeof(struct sockaddr_in);

  //int nbMessage = 2000;
  //while(nbMessage > 0)
  //{
    cout << "Taper un message : " << endl;

    cin.clear();
    cin.getline(msg, 100);
  
    int retourSend = sendto(desc, msg, 100, 0, (struct sockaddr *)adrDist, taille);
    
    if(retourSend <= 0)
    {
      cout << "Message non envoyé..." << endl;
    }
    //else
    //{
      //nbMessage--;
    //}
  //}
  while(true)
  {   
    cout << "Attente d'un message" << endl;
    int retourRec = recvfrom(desc,reception,100, 0, NULL, NULL);
    if(retourRec > 0)
    {
      cout << "Message reçu : " << reception << endl;
      break;
    }
  }
  return 0; 
}

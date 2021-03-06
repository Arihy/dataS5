//MOHAMED EL-HAD Mellany
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include "sock.h"
#include "sockdist.h"
#include <arpa/inet.h>


using namespace std;

int main(int argc, char* argv[])
{
  //cout << "création de la boite" << endl;
  Sock boite(SOCK_DGRAM, 0, 0);
  int desc;
  if(boite.good()){
    desc = boite.getsDesc();
  }
  else{
    cout << "pb BR local" << endl;
    return 1;
  }
  //cout << "declaration des buffers" << endl;
  
  char msg[100];
  char reception[100];
  
  SockDist boiteDistant(argv[1], (short)31469);
  struct sockaddr_in *adrDist = boiteDistant.getAdrDist();
  int taille = sizeof(struct sockaddr_in);
  //cout << "avt sendto" << endl;

  cout << "taper un message, pour arreter le message doit commencer par le caractere '?'" << endl;
  
  while(msg[0] != '?'){
    cin.clear();
    
    cin.getline(msg, 100);
    
    if(msg[0] == '?')
      return 1;
    
    int retourSend = sendto(desc, msg, 100, 0, (struct sockaddr *)adrDist, taille);
    //cout << "apres sendto" << endl;
    
    if(retourSend <= 0)
    {
      cout << "retourSend != 0" << endl;
    }
    
    int retourRec = recvfrom(desc,reception,100, 0, NULL, NULL);
    if(retourRec > 0)
    {
      cout << "message retour : " << reception << endl;
    }
  }
  return 0; 
}

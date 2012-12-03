#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "sock.h"
#include "sockdist.h"
#include <arpa/inet.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
 fd_set multiplexe;
 int nbMaxCli = 10 ; // nbr de client maximum
 int nbCli = 0; // nbre de client connecté
 int tabCli[nbMaxCli]; // tableau avec tous les clients
 int descMax = 0; // descripteur le plus grand
  
 // Creation de la BR locale

 Sock brPub(SOCK_STREAM, (short)(31031), 0); // CrÃ©ation d'une BR TCP
 int descBrPub; 
  
 if (brPub.good())
 {
  descBrPub = brPub.getsDesc();
 }
 else
 {
  cout << "Probleme sur la BR locale" << endl;
  exit(1);
 }

 int estin = listen(descBrPub,5);// ecoute pour la connection, file d'attente de 5  
 struct sockaddr_in brCv;
 socklen_t lgbrCv = sizeof(struct sockaddr_in);

 cout<<"Serveur en attente de connexion: "<<endl;

 while (1)
 {
  FD_ZERO(&multiplexe); // initialisation Ã  faux
  FD_SET(descBrPub,&multiplexe); // positionne a vrai
  descMax = descBrPub;
  for (int i=0; i < nbCli ;i++)// tableau de client
  {
    FD_SET(tabCli[i],&multiplexe);  //position a vrai
    if (descMax < tabCli[i])
      {
	descMax = tabCli[i];
      }
  }
  int retourSelect = select(descMax+1,&multiplexe,NULL,NULL,NULL);// max descMax+1 personne a ecouter
  if (retourSelect == -1 )
  {
   cout << "erreur : commend select  "<<endl;
   close(descBrPub);
   exit(0);
  }
  if(FD_ISSET(descBrPub,&multiplexe))// test sur la Br publique
  {
   if (nbCli < nbMaxCli)//boucle sur les client, recupere le descripteur
   {
    int retourAccept = accept(descBrPub,(struct sockaddr *)&brCv,&lgbrCv);
    if (retourAccept == -1)
    {
     cout << " erreur : command  accept"<<endl;
     close(descBrPub); exit(0);
    }
    tabCli[nbCli] = retourAccept;
    nbCli++;
   }   
  }
  for (int i = 0 ; i < nbCli ; i++)
  {
   if (FD_ISSET(tabCli[i],&multiplexe))// quand un message est envoyee
   {
    //Reception du message
    char msgRecu[100];

    int retourRcv = recv(tabCli[i], msgRecu, sizeof(msgRecu), 0); 

    if (retourRcv == -1)
    {
     cout << " erreur : recv"<<endl;
     close(descBrPub);
     exit(0);
    }
    msgRecu[retourRcv]='\0';// espace resolu ici
    if (retourRcv == 0)//deconection d'une personne 
    { 
      tabCli[i] = tabCli[nbCli];//remplace celui qui part
      nbCli--;
    }
    
    cout << msgRecu<<endl; // affichage du message sur le serveur
    
    for (int j = 0; j < nbCli ; j++)// renvoi a tous les clients
    {
     int retourSend = send(tabCli[j], msgRecu, sizeof(char[100]),0);
     if (retourSend == -1)
     { 
      cout << " erreur : send"<<endl;
      close(descBrPub);
      exit(0);
     } 
    }
   }
  }
  
 }
 
 close(descBrPub);
 return 0;
}

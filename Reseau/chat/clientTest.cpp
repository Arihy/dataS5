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
 if (argc !=3)
 {
  cout << "erreur : oublie de l'adresse de l'hote" << endl;
  exit(1);
 }

 //Identifiant chat
 char iden[200]="";
 char deuxpoint[4]; deuxpoint[0]=' ';deuxpoint[1]=':';deuxpoint[2]=' ';deuxpoint[3]='\0';
 cout<<"Entrez votre identifiant: "<<endl;
 cin.getline(iden, 200);
 int tailleiden=3;
 for(int i=0;i<200;i++){if(iden[i]!='\0'){tailleiden++;}}
 cout<<"la taille iden"<<tailleiden<<endl;
 strcat (iden, deuxpoint);
 cout<<"voici l iden save "<<iden<<endl;
 cout<<"identifiant enregister, discutez: "<<endl;

 // Creation de la BR locale
 Sock brCli(SOCK_STREAM, 0); // CrÃ©ation d'une BR TCP
 int descBrCli;

 if (brCli.good())
 {
  descBrCli = brCli.getsDesc();
 }
 else
 {
  cout << "Probleme sur la boite rÃ©seau locale" << endl;
  exit(1);
 }

 SockDist brPub(argv[1],atoi(argv[2]));//demande de connection sur BR Publique
 struct sockaddr_in * adrBrPub = brPub.getAdrDist();
 int lgAdrBrPub = sizeof(struct sockaddr_in);

 int erlude = connect(descBrCli, (struct sockaddr *)adrBrPub,lgAdrBrPub);//connect sur un listen
 while (1)
 {
  FD_ZERO(&multiplexe); //vide l'ensemble de lecture
  FD_SET(descBrCli,&multiplexe); //ecoute
  FD_SET(0,&multiplexe);//positionner a vrai le clavier
  int retourSelect = select(descBrCli+1,&multiplexe,NULL,NULL,NULL);
  if (retourSelect == -1 )
  {
   cout << "erreur : select ne marche pas "<<endl;
   close(descBrCli);
   exit(0);
  }
  if (FD_ISSET(descBrCli,&multiplexe))// activitÃ© depuis le serveur
  {
   char msgRecu[100];
    int retourRcv = recv(descBrCli, msgRecu, sizeof(msgRecu), 0);
   if (retourRcv == -1)
   {
    cout << " erreur : recv ne marche pas"<<endl;
    close(descBrCli);
    exit(0);
   }
   if (retourRcv == 0)
   {
    cout << " erreur : le serveur est deconnecte"<<endl;
    close(descBrCli);
    exit(0);
   }
    msgRecu[retourRcv]='\0';
   cout << msgRecu <<endl ;
  }
  if (FD_ISSET(0,&multiplexe))//activitÃ© du clavier
  {
      char msg_envoi[100];
   cin.getline(msg_envoi,100);
   strcat(iden,msg_envoi);
   cout<<"ceci est le test"<<iden<<" cecci c ca"<<endl;
   int retourSend = send(descBrCli,iden, 200, 0);
   iden[tailleiden]=0;//enleve tout ce qu'il y a après
   if (retourSend == -1 )
   {
    cout << " erreur : send ne marche pas"<<endl;
    close(descBrCli);
    exit(0);
   }
  }

 }

 close(descBrCli);
 return 0;
}

//client
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


int main(int argc, char **argv, char **env)
{
	if(argc != 3)
	{
		cout << "erreur de parametrage!" << endl;
		return -1;
	}

	//Preparation de la BR client
	Sock brClient(SOCK_STREAM, 0);
	int descBrCli;
	if(brClient.good())
		descBrCli = brClient.getsDesc();
	else
	{
		cout << "Pb BR client" << endl;
		return -1;
	}

	SockDist brPublic(argv[1], atoi(argv[2]));
	struct sockaddr_in* adrBrPub = brPublic.getAdrDist();
	int lg = sizeof(struct sockaddr_in);

	//pseudo
	char prefixeEtMsg[200] = ""; //un peu plus qu'un twitte
	cout << "entrer un pseudo" << endl;
	cin.getline(prefixeEtMsg, 200);
	int taille = strlen(prefixeEtMsg);
	prefixeEtMsg[taille] = ' ';
	taille++;
	prefixeEtMsg[taille] = ':';
	taille++;
	prefixeEtMsg[taille] = ' ';
	taille++;
	cout << "pseudo enregistre est " << prefixeEtMsg << endl;

	fd_set fdRead;
	int resConnect = connect(descBrCli, (struct sockaddr *)adrBrPub, lg);
	int resSelect;
	int resAccept;
	int resSend;
	int resRecv;
	char reception[200];

	while(true)
	{
		FD_ZERO(&fdRead);
		FD_SET(descBrCli, &fdRead);
		FD_SET(0, &fdRead);
		if((resSelect = select(descBrCli+1, &fdRead, NULL, NULL, NULL)) == -1)
		{
			perror("erreur select");
			close(descBrCli);
			return -1;
		}
		//cout << "select ok !" << endl;

		if(FD_ISSET(descBrCli, &fdRead)) //mouvement serveur donc reception
		{
			//cout << "quelqu'un a bougé" << endl;
			if((resRecv = recv(descBrCli, reception, sizeof(reception), 0)) == -1)
			{
				perror("erreur recv");
				close(descBrCli);
				return -1;
			}

			if(resRecv == 0)
			{
				cout << "le serveur est deconecte..." << endl;
				close(descBrCli);
				return -1;
			}
			//cout << "message recu" << endl;

			reception[resRecv] = '\0';
			cout << ">>  " << reception << endl;
		}

		if(FD_ISSET(0, &fdRead)) //mouvement clavier donc envoie
		{
			cin.getline(&(prefixeEtMsg[taille]), 200);
			//test si message taper est un exit
			if(prefixeEtMsg[taille] == 'e' && prefixeEtMsg[taille+1] == 'x' && prefixeEtMsg[taille+2] == 'i' && prefixeEtMsg[taille+3] == 't')
			{
				resSend = send(descBrCli,prefixeEtMsg, 200, 0);
				return -1;
			}
			resSend = send(descBrCli,prefixeEtMsg, 200, 0);
			//prefixeEtMsg[taille] = 0;//enleve tout ce qu'il y a après
   		if(resSend == -1 )
   		{
				perror("erreur");
    		close(descBrCli);
				return -1;
   		}
			//cout << "message envoyé" << endl;
		}
		
	}


	return 0;
}

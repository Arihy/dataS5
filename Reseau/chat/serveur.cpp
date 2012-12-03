/*serveur
Le serveur crash quand un client se deconnecte.
*/

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

#define NB_CLIENT_MAX 10
#define TAILLE_LISTEN 10
#define TAILLE_RECEPTION 200;

using namespace std;

int main(int argc, char** argv, char** env)
{
	if(argc != 2)
	{
		cout << "erreur de parametre!" << endl;
		return -1;
	}
	//Preparation de la BR public
	cout << "Preparation de la BR public" << endl;
	Sock brServeur(SOCK_STREAM, atoi(argv[1]), 0);
	int descBrS;
	if(brServeur.good())
		descBrS = brServeur.getsDesc();
	else
	{
		cout << "Pb BR" << endl;
		return 1;
	}

	int resListen = listen(descBrS, 10); //liste d'attente de taille 10, si plus de client, rejeté
	if(resListen == -1)
	{
		cout << "erreur Listen" << endl;
		exit(0);
	}

	int listClient[10];

	//Creationd du CV
	struct sockaddr_in brCv;
	socklen_t lgbrCv = sizeof(struct sockaddr_in);

	fd_set fdRead;
	int resSelect;
	int resAccept;
	int resSend;
	int resRecv;
	int nbConnecte = 0;
	int descMax = 0;
	cout << "serveur connecté" << endl;
	while(true)
	{
		FD_ZERO(&fdRead);
		FD_SET(descBrS, &fdRead);
		descMax = descBrS;
		for(int i = 0; i < nbConnecte; i++)
		{
			FD_SET(listClient[i], &fdRead);
			if(descMax < listClient[i])
			{
				descMax = listClient[i];
			}
		}
		resSelect = select(descMax+1, &fdRead, NULL, NULL, NULL);
		if(resSelect == -1)
		{
			perror("erreur select");
			close(descBrS);
			exit(0);
		}
		//else cout << "select OK!" << endl;


		if(FD_ISSET(descBrS, &fdRead))
		{
			if(nbConnecte < NB_CLIENT_MAX)
			{	
				resAccept = accept(descBrS, (struct sockaddr *)&brCv, &lgbrCv);
				if(resAccept == -1)
				{
					perror("erreur accept");
					close(descBrS);
					exit(0);
				}
				listClient[nbConnecte] = resAccept;
				nbConnecte++;
				cout << "Nb connecte = " << nbConnecte << endl;
			}
		}

		for(int i = 0; i < nbConnecte; i++)
		{
			if(FD_ISSET(listClient[i], &fdRead)) /////ne rentre pas dans cette condition
			{
				//cout << "quelqu'un a bougé" << endl;
				char reception[200];
				if((resRecv = recv(listClient[i], reception, sizeof(reception), 0)) == -1)
				{
					perror("erreur recv");
					close(descBrS);
					exit(0);
				}
				//cout << "message reçu" << endl;
				reception[resRecv] = '\0';
				//cout << reception << endl;
				if(resRecv == 0)
				{
					listClient[i] = listClient[nbConnecte];
					nbConnecte--;
					cout << "Nb connecte = " << nbConnecte << endl;
				}

				//renvoie le message reçu a tout les clients connecté
				for(int j = 0; j < nbConnecte; j++)
				{
					resSend = send(listClient[j], reception, sizeof(char[200]), 0);
					if(resSend == -1)
					{
						perror("erreur send");
						close(descBrS);
						exit(0);
					}
					//cout << "message envoye !!" << endl;
				}
			}
		}
	}
	close(descBrS);
	return 0;
}

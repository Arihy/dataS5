//serveur
#include <iostream> 
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "sock.h"
#include "sockdist.h"
#include <arpa/inet.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv, char** env)
{
	Sock brServeur(SOCK_STREAM, 31031, 0);
	int desc;
	if(brServeur.good())
		desc = brServeur.getsDesc();
	else
	{
		cout << "Pb BR" << endl;
		return 1;
	}

	int res = listen(desc, 5); //liste d'attente de taille 5, si plus de client, rejeté
	struct sockaddr_in brCv;
	socklen_t lg = sizeof(sockaddr_in);
	int descBrCv = accept(desc, (struct sockaddr*)&brCv, &lg);

	uid_t id;
	
	while(true)
	{
		int s = recv(descBrCv, &id, sizeof(uid_t), 0);
		if(s > 0)
		{
			cout << "message reçu: " << id << endl;
			break;
		}
	}

	char msg[] = "Tiens, bonjour ";
	struct passwd* structure = getpwuid(id);
	strcat(msg, structure->pw_name);
	int s2 = send(descBrCv, msg, strlen(msg), 0);
	
	close(desc);
	return 0;
}

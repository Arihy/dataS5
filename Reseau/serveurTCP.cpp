#include <iostream> 
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "sock.h"
#include "sockdist.h"
#include <arpa/inet.h>
#include <string.h>

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
	int descBrCv = accept(brServeur, (struct sockaddr*)&brCv, &lg);

	char buffer[256];
	int s = recv(descBrCv, buffer, 256, 0);
	char msg = "Tiens, bonjour...";
	int s2 = send(descBrCv, msg, strlen(msg), 0);

	return 0;
}

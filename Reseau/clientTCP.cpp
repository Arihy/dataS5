#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "sock.h"
#include "sockdist.h"
#include <arpa/inet.h>



unsing namespace std;

int main(int argc, char** argv, char** env)
{
	Sock brClient(SOCK_STREAM, 0);
	int descBrCli;
	if(brClient.good())
		descBrCli = brClient.getsDesc();
	else
	{
		cout << "Pb BR" << endl;
		return 1;
	}

	SockDist brPublic(argv[1], atoi(argv[2]);
	struct sockaddr_in* adrBrPub = brPub.getAdrDist();
	int lg = sizeof(struct sockaddr_in);

	int resCo = connect(descBrCli, (struct sockaddr*)adrBrPub, lg);

	char buffer[256];
	char msg[] = "coucou";
	if(resCo != -1)
		int s = send(descBrCli, msg, strlen(msg), 0);

	int s2 = recv(descBrCli, buffer, 256, 0);
	return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <iostream.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fstream.h>

#include "sock.h"
#include "sockdist.h"

main(int argc, char * argv[]){

/* On ne tient pas compte du nombre de param�tres. Il ne devrait
pas y en avoir */

/* Une BR locale */
Sock maBR (SOCK_DGRAM, (short)0, 0);
int descmaBR;

if (maBR.good()){
	descmaBR=maBR.getsDesc();//on recupere le descripteur
}
else {
	cout<<"pb BR locale"<<endl;
	exit(1);
}
cout<<"BR locale créée"<<endl;
//On prepare le necessaire pour reconnaitre l'expediteur
//et on recupere son message.
SockDist saBR(argv[1], (short)31469);
//socklen_t lgsaBR = saBR.getsLen();
int lgsaBR = sizeof(struct sockaddr_in);
sockaddr_in *adrsaBR = saBR.getAdrDist();

char msg[700];
cout<<"entrez un message"<<endl;
cin>>msg;

int retourSend=sendto(descmaBR, msg, 700, 0, (struct sockaddr *) adrsaBR, lgsaBR);
	if (retourSend < 0){
		cout <<"pas de message envoyé"<<endl;
		return 1;
	}
	else{
		cout <<"message envoyé"<<endl;
	}


char tamponReception[500];

int retourRecv=recvfrom(descmaBR, tamponReception, 500, 0, NULL, NULL);
	if (retourRecv < 0){
		cout <<"pas de message reçu"<<endl;
		return 1;
	}
	else{
		cout <<"message reçu : "<< tamponReception << endl;
		
	}
return 0;
	
}





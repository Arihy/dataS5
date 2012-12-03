#FLAGS=-Wall
C=g++ $(FLAGS)

all: client serveur

client: client.cpp sock.o sockdist.o
	$C -o client client.cpp sock.o sockdist.o

serveur: serveur.cpp sock.o sockdist.o
	$C -o serveur serveur.cpp sock.o sockdist.o

sock.o: sock.cc
	$C -c sock.cc

sockdist.o: sockdist.cc
	$C -c sockdist.cc

clean:
	rm -f *.o serveur client

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
//protos
void grapherandom(int n, int m, int edge[][2]);
void affichage(int m, int edge[][2]);
void affichage1D(int n, int comp[]);
void composantes(int n, int m, int edge[][2], int comp[]);

int main(){ 
    int n;     // Nombre de sommets.	
    int m;     // Nombre d'aretes.	
    cout << "Entrer le nombre de sommets:";
    cin >> n;
    cout << "Entrer le nombre d'aretes:";
    cin >> m;
    int edge[m][2];    // Tableau des aretes.
    int comp[n];       // comp[i] est le numero de la composante contenant i.

    grapherandom(n, m, edge);
    affichage(m, edge);
    composantes(n, m, edge, comp);
    affichage1D(n, comp);


    return 0;
}

void grapherandom(int n, int m, int edge[][2])
{
  srand(time(NULL));
  for(int i = 0; i < m; i++){
    edge[i][0] = rand()%n;
    edge[i][1] = rand()%n;
  }
}

void affichage(int m, int edge[][2])
{
  cout << "{";
  for(int i = 0; i < m; i++){
    cout << "{" << edge[i][0];
    cout << edge[i][1] << "}";
  }
  cout << "} \n";
}

void affichage1D(int n, int comp[])
{
  cout << "{";
  for(int i = 0; i < n; i++){
    cout << " " << comp[i];
  }
  cout << "} \n";
}

void composantes(int n, int m, int edge[][2], int comp[])
{
  int aux = 0;
  for(int i = 0; i < n; i++){
    comp[i] = i;
  }
  for(int i = 0; i < m; i++){
    if(comp[edge[i][0]] != comp[edge[i][1]]){
      aux = comp[edge[i][0]];
      for(int j = 0; j < n; j++){
	if(comp[j] == aux){
	  comp[j] = comp[edge[i][1]];
	}
      }
    }
  }
}

void ecritureTailles(int n, int m, int comp[])
{
}

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
//protos
void grapherandom(int n, int m, int edge[][2]);
void affichage(int m, int edge[][2]);
void affichage1D(int n, int comp[]);
void composantes(int n, int m, int edge[][2], int comp[]);
void ecritureTailles(int n, int m, int comp[]);
int nbOccurence(int n, int comp[], int x);
void composantesOpt(int n, int m, int edge[][2], int comp[]);

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
    cout << "edge   "; 
    affichage(m, edge);
    composantes(n, m, edge, comp);
    cout << "composante   ";
    affichage1D(n, comp);
    composantesOpt(n, m, edge, comp);
    cout << "composante optimisee ";
    affichage1D(n, comp);
    ecritureTailles(n, m, comp);


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

int nbOccurence(int n, int comp[], int x)
{
  int nb = 0;
  for(int i = 0; i < n; i++)
    {
      if(comp[i] == x)
	nb++;
    }
  return nb;
}

void ecritureTailles(int n, int m, int comp[])
{
  int nb = 0;
  int nbComp[n];
  int tailleComp[n];
  for(int i = 0; i < n; i++)
    {
      nbComp[i] = i;
      tailleComp[i] = i;
    }
  for(int i = 0; i < n; i++)
    {
      nbComp[i] = nbOccurence(n, comp, i);
    }
  cout << "nb comp ";
  affichage1D(n, nbComp);
  for(int i = 0; i < n; i++)
    tailleComp[i] = nbOccurence(n, nbComp, i);
  cout << "taille comp ";
  affichage1D(n, tailleComp);
  
  cout << "il y a " << tailleComp[0] << " points isoles." <<endl;
  for(int i = 1; i < n; i++)
    if(tailleComp[i] != 0)
      cout << "il y a " << tailleComp[i] << " composantes de taille " << i <<endl;
}


void composantesOpt(int n, int m, int edge[][2], int comp[])
{
  int aux = 0;
  int tmp = 0;
  int z = 0;
  vector<int> compL[n];
  int t[n];
  for(int i = 0; i < n; i++)
  {
    comp[i] = i;
    compL[i].push_back(i);
    t[comp[i]] = 1;
  }
  for(int i = 0; i < m; i++)
  {
    if(comp[edge[i][0]] != comp[edge[i][1]])
    {
      if(t[comp[edge[i][0]]] > t[comp[edge[i][1]]])
      {
	tmp = edge[i][0];
	edge[i][0] = edge[i][1];
	edge[i][1] = tmp;
      }
      aux = comp[edge[i][0]];
      t[comp[edge[i][1]]] = t[comp[edge[i][1]]] + t[aux];
      
      while(!compL[aux].empty())
      {
	z = compL[aux].back();
	compL[comp[edge[i][1]]].push_back(z);
	comp[z] = comp[edge[i][1]];
	compL[aux].pop_back();
      }
    }
  }
}






#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

void pointrandom(int n, int point[][2]);
void voisins(int n, int dmax, int point[][2], vector<int> voisin[]);
void afficherVoisins(int n, vector<int> voisins[]);

int main()
{
  int n;                   //Le nombre de points.
  int m;                   //Le nombre d aretes.
  cout << "Entrer le nombre de points: ";
  cin >> n;

  int dmax=100;             // La distance jusqu'a laquelle on relie deux points.

  vector<int> voisin[n];   // Les listes de voisins.          
  int point[n][2];         // Les coordonnees des points.

  int d[n];                // La distance a la racine.
  int arbre[n-1][2];       // Les aretes de l'arbre de Dijkstra.
  int pere[n];             // La relation de filiation de l'arbre de Dijkstra.

  voisins(n, dmax, point, voisin);
  afficherVoisins(n, voisin);

  return 0;
}

void pointrandom(int n, int point[][2])
{
  srand(time(NULL));
  for(int i = 0; i < n; i++)
  {
    point[i][0] = rand()%612;
    point[i][1] = rand()%792;
  }
}


void voisins(int n, int dmax, int point[][2], vector<int> voisin[])
{
  pointrandom(n, point);
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      if(i != j)
      {
        if(sqrt((point[j][0]-point[i][0])*(point[j][0]-point[i][0])+(point[j][1]-point[i][1])*(point[j][1]-point[i][1])) <= dmax)
        {
          voisin[i].push_back(j);
        }
      }
    }
  }
}

void afficherVoisins(int n, vector<int> voisins[])
{
  for(int i = 0; i < n; i++)
  {
    cout << i << " ->";
    for(int j = 0; j < voisins[i].size(); j++)
    {
      cout << " " << voisins[i][j];
    }
    cout << endl;
  }
}

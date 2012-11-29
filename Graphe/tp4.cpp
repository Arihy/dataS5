#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;
int MAX = 99999;
void pointrandom(int n, int point[][2]);
void voisins(int n, int dmax, int point[][2], vector<int> voisin[]);
void afficherVoisins(int n, vector<int> voisins[]);
void AffichageGraphe(int n, int point[][2], vector<int> voisin[]);
void dijkstra(int n, vector<int> voisin[], int point[][2], int pere[]);
bool traiter(int n, int traite[]);
double longueur(int x, int y, int point[][2]);

int main()
{
  int n;                   //Le nombre de points.
  int m;                   //Le nombre d aretes.
  cout << "Entrer le nombre de points: ";
  cin >> n;

  int dmax=50;             // La distance jusqu'a laquelle on relie deux points.

  vector<int> voisin[n];   // Les listes de voisins.          
  int point[n][2];         // Les coordonnees des points.

  int d[n];                // La distance a la racine.
  int arbre[n-1][2];       // Les aretes de l'arbre de Dijkstra.
  int pere[n];             // La relation de filiation de l'arbre de Dijkstra.

  voisins(n, dmax, point, voisin);
  afficherVoisins(n, voisin);

  AffichageGraphe(n, point, voisin);
  
  cout << "dijkstra" << endl;
  dijkstra(n, voisin, point, pere);
  cout << "fin" <<endl;
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


void AffichageGraphe(int n, int point[][2], vector<int> voisin[])
{
  ofstream output;                           
  output.open("Exemple.ps",ios::out);
  output << "%!PS-Adobe-3.0" << endl;
  output << "%%BoundingBox: 0 0 612 792" << endl;
  output << endl;
  for(int i=0;i<n;i++)
  {
    output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
    output << "0 setgray" <<endl;
    output << "fill" <<endl;
    output << "stroke"<<endl;
    output << endl;
  }
  output << endl;
  for(int i = 0; i < n-1; i++)
  {
    for(int j = 0; j < voisin[i].size(); j++)
    {
      output << point[i][0] << " " << point[i][1] << " moveto" << endl;
      output << point[voisin[i][j]][0] << " " << point[voisin[i][j]][1] << " lineto" << endl;
      output << "stroke" << endl;
      output << endl;
    }
  }
}

bool traiter(int n, int traite[])
{
  for(int i = 0; i < n; i++)
  {
    if(traite[i] == 0)
    {
      return true;
    }
  }
  return false;
}

double longueur(int x, int y, int point[][2])
{
  int a = (point[x][1] - point[y][1]) * (point[x][1] - point[y][1]);
  int b = (point[x][0] - point[y][0]) * (point[x][0] - point[y][0]);
  return sqrt(a + b);
}

void dijkstra(int n, vector<int> voisin[], int point[][2], int pere[])
{
  int d[n];
  int traite[n];
  int x;
  for(int i = 0; i < n; i++)
  {
    pere[i] = -1;
    d[i] = 9999;
    traite[i] = 0;
  }
  pere[0] = 0;
  d[0] = 0;
  //afficherVoisins(n, voisin);
  while(traiter(n, traite))
  {
    int dMax = 9999;
    for(int i = 0; i < n; i++)
    {
      if((dMax > d[i]) && (traite[i] == 0))
      {
        dMax = d[i];
        x = i;
      }
    } 
    traite[x] = 1;
    //cout << "traite[" << x << "] = " << traite[x] << endl;
    for(int j = 0; j < voisin[x].size(); j++)
    {
    	cout << "traite[" << x << "] = " << traite[x] << endl;
      int y = voisin[x][j];
      if(traite[y] == 0 && (d[y] > (d[x] + longueur(x, y, point))))
      {
        d[y] = d[x] + (int)longueur(x, y, point);
        pere[y] = x;
      }
    }
  }
}

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void affichage(int n, int tab[][2]);
void pointrandom(int n, int point[][2]);
void distance(int n, int m, int point[][2], int edge[][3]);
void affichage(int n, int tab[][3]);
void tri(int m, int edge[][3]);
void kruskal(int n, int m, int edge[][3], int arbre[][2]);
void AffichageGraphique(int n, int point[][2], int arbre[][2]);

int main(){
  int n;             //Le nombre de points.
  cout << "Entrer le nombre de points: ";
  cin >> n;
  int m=n*(n-1)/2;   // Le nombre de paires de points.
  int point[n][2];   // Les coordonnees des points dans le plan.
  int edge[m][3];    // Les paires de points et le carre de leur longueur.
  int arbre[n-1][2]; // Les aretes de lâ€™arbre de Kruskal.

  pointrandom(n, point);
  cout << "point ";
  affichage(n, point);
  cout << endl;

  distance(n, m, point, edge);
  cout << "edge ";
  affichage(m, edge);
  cout << endl;

  tri(m, edge);
  cout << "edge trie ";
  affichage(m, edge);
  cout << endl;

  kruskal(n, m, edge, arbre);
  cout << "arbre ";
  affichage(n-1, arbre);

  AffichageGraphique(n, point, arbre);


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

void affichage(int n, int tab[][2])
{
  cout << "{";
  for(int i = 0; i < n; i++)
  {
    cout << endl;
    cout << "{" << tab[i][0] << "," << tab[i][1] << "}";
  }
  cout << "}" << endl;
}


void distance(int n, int m, int point[][2], int edge[][3])
{
  int k = 0;
  for(int i = 0; i < n-1; i++)
  {
    for(int j = i+1; j < n; j++)
    {
      edge[k][0] = i;
      edge[k][1] = j;
      edge[k][2] = (point[j][0]-point[i][0])*(point[j][0]-point[i][0])+(point[j][1]-point[i][1])*(point[j][1]-point[i][1]);
      k++;
    }
  }
}


void affichage(int n, int tab[][3])
{
  cout << "{";
  for(int i = 0; i < n; i++)
  {
    cout << endl;
    cout << "{" << tab[i][0] << "," << tab[i][1] << "," << tab[i][2] << "}";
  }
  cout << "}" << endl;
}


void tri(int m, int edge[][3])
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < m-1; j++)
    {
      if(edge[j][2] > edge[j+1][2])
      {
	int tmp = edge[j][0];
	edge[j][0] = edge[j+1][0];
	edge[j+1][0] = tmp;

	tmp = edge[j][1];
	edge[j][1] = edge[j+1][1];
	edge[j+1][1] = tmp;

	tmp = edge[j][2];
	edge[j][2] = edge[j+1][2];
	edge[j+1][2] = tmp;
      }
    }
  }
}


void kruskal(int n, int m, int edge[][3], int arbre[][2])
{
  int aux = 0;
  int tmp = 0;
  int z = 0;
  int comp[n];
  int j = 0;
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
      arbre[j][0] = edge[i][0];
      arbre[j][1] = edge[i][1];
      j++;
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

void AffichageGraphique(int n, int point[][2], int arbre[][2])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("Exemple.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;  
 for(int i=0;i<n;i++)
   {output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
   output << "0 setgray" <<endl;
   output << "fill" <<endl;
   output << "stroke"<<endl;
   output << endl;
   }
 output << endl;
 for(int i=0;i<n-1;i++)
   {output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] 
	   << " moveto" << endl;
   output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] 
	  << " lineto" << endl;
   output << "stroke" << endl;
   output << endl;
   }
}

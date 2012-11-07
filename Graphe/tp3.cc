#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
void voisinstrandom(int n, int m, vector<int> voisins[]);
bool appartient(int x, vector<int> voisins);
void afficherVoisins(int n, vector<int> voisins[]);
void parcourslargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]);
void affichage(int n, int tab[]);
int nbOccurence(int n, int niveau[], int x);
void ecritureniveaux(int n, int niveau[]);

int main(){
  int n;             //Le nombre de sommets.
  int m;             // Le nombre d'aretes.
  cout << "Entrer le nombre de sommets: ";
  cin >> n;
  cout << "Entrer le nombre d'aretes: ";
  cin >> m;
  vector<int> voisins[n];	// Les listes des voisins. 
  int pere[n];            // L'arbre en largeur.
  int ordre[n];           // L'ordre de parcours.
  int niveau[n];          // Le niveau du point.

  voisinstrandom(n, m, voisins);
  afficherVoisins(n, voisins);
  
  parcourslargeur(n, voisins, niveau, ordre, pere);
  cout << "pere : " << endl;
  affichage(n, pere);

  cout << "ordre : " << endl;
  affichage(n, ordre);

  cout << "niveau : " << endl;
  affichage(n, niveau);
  cout << endl;

  ecritureniveaux(n, niveau);




  return 0;
}




void voisinstrandom(int n, int m, vector<int> voisins[])
{
  srand(time(NULL));
  int arete = m;
  int sommet = 0;
  int y = 0;
  while(arete != 0)
  {
    y = rand()%n;
    sommet = rand()%n;
    if(sommet != y && !appartient(y, voisins[sommet])) //(appartient) pas d'arret multiple
    {
      voisins[sommet].push_back(y);
      voisins[y].push_back(sommet);
      arete--;
    }
  }
}


bool appartient(int x,  vector<int> voisins)
{
  for(int i = 0; i < voisins.size(); i++)
  {
    if(x == voisins[i])
       return true;
  }
  return false;
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


void parcourslargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[])
{
  int dv[n];
  int t = 2;
  vector<int> AT;
  int debut = 0;
  int fin = n-1;
  int v = 0;
  for(int i = 0; i < n; i++)
  {
    dv[i] = 0;
  }

  dv[0] = 1;
  ordre[0] = 1;
  pere[0] = 0;
  niveau[0] = 0;
  AT.push_back(0);
  while(AT.size() != 0)
  {
    v = AT.back();
    AT.erase(AT.begin());
    
    for(int i = 0; i < voisins[v].size(); i++)
    {
      if(dv[voisins[v][i]] == 0)
      {
	dv[voisins[v][i]] = 1;
	AT.push_back(voisins[v][i]);
	ordre[voisins[v][i]] = t;
	t++;
	pere[voisins[v][i]] = v;
	niveau[voisins[v][i]] = niveau[v] + 1;
      }
    }
  }
}
void affichage(int n, int tab[])
{
  for(int i = 0; i < n; i++)
  {
    cout << i << " ";
  }
  cout << endl;
  for(int i = 0; i < n; i++)
  {
    cout << tab[i] << " ";
  }
  cout << endl;
}

int nbOccurence(int n, int niveau[], int x)
{
  int nb = 0;
  for(int i = 0; i < n; i++)
  {
    if(niveau[i] = x)
      nb++;
  }
  return nb;
}

void ecritureniveaux(int n, int niveau[])
{
  int nb = 0;
  int nbNiveaux[n];
  int tailleNiveaux[n];
  for(int i = 0; i < n; i++)
  {
    nbNiveaux[i] = i;
    tailleNiveaux[i] = i;
  }

  for(int i = 0; i < n; i++)
  {
    nbNiveaux[i] = nbOccurence(n, niveau, i);
  }

  for(int i = 0; i < n; i++)
  {
    tailleNiveaux[i] = nbOccurence(n, nbNiveaux, i);
  }

  nb = 0;
  cout << "il y a " << tailleNiveaux[0] << " sommets au niveau 0" << endl;
  for(int i = 1; i < n; i++)
  {
    if(tailleNiveaux[i] != 0)
       cout << "il y a " << tailleNiveaux[i] << " sommets au niveau " << i << endl;
    else
       nb++;
  }
  cout << "il y a " << nb << " sommets qui ne sont pas dans la composante de 0." << endl;
}

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
void voisinstrandom(int n, int m, vector<int> voisins[]);
bool appartient(int x, vector<int> voisins);
void afficherVoisins(int n, vector<int> voisins[]);
void parcourslargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]);
void parcoursprofondeur(int n, vector<int> voisins[], int debut[], int fin[], int pere[]);
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
  int debut[n];
  int fin[n];

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
  cout << endl;
  cout << "PROFONDEUR" << endl << endl;
  parcoursprofondeur(n, voisins, debut, fin, pere);
  cout << "pere : " << endl;
  affichage(n, pere);

  cout << "debut : " << endl;
  affichage(n, debut);

  cout << "fin : " << endl;
  affichage(n, fin);
  cout << endl;

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
  for(int i = 0; i < n; i++)
  {
    niveau[i] = -1;
    ordre[i] = -1;
    pere[i] = -1;
  }
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
    if(niveau[i] == x)
      nb++;
  }
  return nb;
}

void ecritureniveaux(int n, int niveau[])
{
  int nb = 0;
  int nbNiveaux[n];
  for(int i = 0; i < n; i++)
  {
    nbNiveaux[i] = 0;
  }

  for(int i = 0; i < n; i++)
  {
    nbNiveaux[i] = nbOccurence(n, niveau, i);
  }
  int nbSommetLibre = nbOccurence(n, niveau, -1);
  for(int i = 0; i < n; i++)
  {
    if(nbNiveaux[i] != 0)
       cout << "il y a " << nbNiveaux[i] << " sommet(s) au niveau " << i <<"."<< endl;
  }
  cout << "il y a " << nbSommetLibre << " sommet(s) qui ne sont pas dans la composante de 0." << endl;
}


void parcoursprofondeur(int n, vector<int> voisins[], int debut[], int fin[], int pere[])
{
  for(int i = 0; i < n; i++)
  {
    debut[i] = -1;
    fin[i] = -1;
    pere[i] = -1;
  }
  int dv[n];
  int t = 2;
  vector<int> AT;
  for(int i = 0; i < n; i++)
  {
    dv[i] = 0;
  }
  int r = 0;
  int y;
  dv[r] = 1;
  pere[r] = r;
  debut[r] = 1;
  AT.push_back(r);
  while(AT.size() != 0)
  {
    //r sommet en haut de AT
    r = AT.back();
    if(voisins[r].size() == 0)
    {
       AT.pop_back();
       fin[r] = t;
       t += 1;
    }
    else
    {
       y = voisins[r].back();
       voisins[r].pop_back();
       if(dv[y] == 0)
       {
          dv[y] = 1;
          AT.push_back(y);
          debut[y] = t;
          t += 1;
          pere[y] = r;
       }
    }
  }
}

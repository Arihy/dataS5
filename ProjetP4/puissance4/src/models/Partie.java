package models;

public class Partie {
	Joueur joueur1;
	Joueur joueur2;
	Grille grille;
	Etat etat;
	
	public Partie()
	{
		joueur1 = new Joueur("inconnu1", 1);
		joueur2 = new Joueur("inconnu2", 2);
		grille = new GrilleNormale();
		etat = new Etat();
	}
	
	public Partie(Joueur j1, Joueur j2, int niveau)
	{
		joueur1 = j1;
		joueur2 = j2;
		if(niveau == 1)
			grille = new Grille();
		etat = new Etat();
	}
}

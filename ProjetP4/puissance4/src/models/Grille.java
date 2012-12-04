package models;

public class Grille {
	int nbLigne; //nb de case dans une colonne
	int nbColonne;
	Colonne colonnes[];
	
	public Grille()
	{
		nbLigne = 6;
		nbColonne = 7;
		colonnes = new Colonne[nbColonne];
	}
}

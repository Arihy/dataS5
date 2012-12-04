package models;

public class Colonne {
	int nbLigne;
	Case cases[];
	public Colonne()
	{
		nbLigne = 6;
		cases = new Case[nbLigne];
	}
	
	public Colonne(int nbLigne)
	{
		this.nbLigne = nbLigne;
		cases = new Case[nbLigne];
	}
	
	public int getTaille()
	{
		return nbLigne;
	}
	
	public Case getCase(int i)
	{
		return cases[i];
	}
	
	public boolean estVide()
	{
		return cases[nbLigne-1].estVide();
	}
	
	public boolean estPleine()
	{
		return !(cases[0].estVide());
	}
	
	public int premiereCaseVide()
	{
		if(estVide())
			return nbLigne-1;
		if(estPleine())
			return -1;
		int i = 0;
		while(i < nbLigne)
		{
			if(cases[i].estVide())
				i++;
		}
		return i-1;
	}
}

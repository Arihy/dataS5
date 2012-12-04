package models;

public class Jeu {
	Partie partie;
	
	public Jeu()
	{
		partie = new Partie();
	}
	
	public void nouvellePartie()
	{
		partie = new Partie();
	}
	
}

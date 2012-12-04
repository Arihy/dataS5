package controllers;
import models.Colonne;
import models.Jeu;

public class Application {

	public static void joueurSurCase(int numJoueur, Colonne c)
	{
		for(int i = 0; i < c.getTaille()-1; i++)
		{
			if(c.estPleine())
			{
				System.out.println("jouez sur une autre colonne...");
			}
			else
			{
				//on recupere la premiere case vide de la colonne en partant du bas.
				c.getCase(c.premiereCaseVide()).setValeur(numJoueur);
			}
		}
	}
	public static void main(String[] args) {
		Jeu jeu = new Jeu();
	}

}

package models;

public class Case {
	//coordonnée
	private boolean vide;
	private int valeur;
	
	public Case()
	{
		vide = true;
		valeur = -1;
	}
	
	public int getValeur()
	{
		return valeur;
	}
	
	public void setValeur(int v)
	{
		valeur = v;
		vide = false;
	}
	
	public boolean estVide()
	{
		if(vide)
			return true;
		return false;
	}
	
	public void setVide(boolean b)
	{
		vide = b;
	}

}

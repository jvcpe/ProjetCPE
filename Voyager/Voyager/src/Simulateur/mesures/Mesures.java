package Simulateur.mesures;

import Simulateur.Coord;
import Simulateur.environnement.EnviRobot;
import Simulateur.environnement.TypeCase;

public class Mesures {
	

	private int nbCommandes;
	private int nbObstaclesVisibles;
	private int nbObstaclesRencontres;
	private int distanceParcourue;
	
	public Mesures(){
		super();
	}
	
	
	public void obstaclesRencontresMaj(EnviRobot env){
		int ret=0;
		for(int i=0;i<env.getTaille().x;i++)
		{
			for(int j=0;j<env.getTaille().y;j++)
			{
				if(env.contenuCase(new Coord(i,j))==TypeCase.obstacle)
						ret++;
					
			}
		}
		this.nbObstaclesRencontres=ret;
	}
	
	public void upgradeDistanceParcourue() {
		distanceParcourue++;
		
	}
	
	public void upgradeCommande() {
		this.nbCommandes++;
		
	}
	
	
	public void obstaclesVisiblesMaj(int nb){
		this.nbObstaclesVisibles=nb;
	}
	
	
	
	//getters et setters
	public int getNbCommandes() {
		return nbCommandes;
	}
	public void setNbCommandes(int nbCommandes) {
		this.nbCommandes = nbCommandes;
	}
	public int getNbObstaclesVisibles() {
		return nbObstaclesVisibles;
	}
	public void setNbObstaclesVisibles(int nbObstaclesVisibles) {
		this.nbObstaclesVisibles = nbObstaclesVisibles;
	}
	public int getNbObstaclesRencontres() {
		return nbObstaclesRencontres;
	}
	public void setNbObstaclesRencontres(int nbObstaclesRencontres) {
		this.nbObstaclesRencontres = nbObstaclesRencontres;
	}
	public int getDistanceParcourue() {
		return distanceParcourue;
	}
	public void setDistanceParcourue(int distanceParcourue) {
		this.distanceParcourue = distanceParcourue;
	}




}

package Simulateur.environnement;

import Simulateur.Coord;

public class Map {



	private Case[][] terrain=new Case[24][24]; 
	public Map(){}

	public Map(int x,int y,double proba){
	
		for(int i=0;i<x;i++)
		{
			for(int j=0;j<y;j++)
			{
				if(Math.random() > (proba/100)){
					this.terrain[i][j]=new Case(TypeCase.vide);
				}
				else{
					this.terrain[i][j]=new Case(TypeCase.obstacle);
				}
			}
		}
	}
	
	
	public TypeCase contenuCase(Coord coord){
		TypeCase ret=TypeCase.vide;
		//System.out.println("x: "+ coord.x + " y: "+ coord.y);
		ret=this.terrain[coord.x][coord.y].getType();
		return ret;
	}

	public Case[][] getTerrain() {
		return terrain;
	}


	public void setCase(Coord coord, Case type) {
		this.terrain[coord.x][coord.y] =type ;
	}


}

package Simulateur.environnement;

import java.util.Formatter;
import java.util.Locale;

import Simulateur.Coord;


public class EnviDev extends AbstractEnvi {



	private Map map;
	private Coord taille;

	
	public EnviDev(int proba,int x,int y){
		if(x<5)x=6;
		if(y<5)y=6;
		if(x>25)x=24;
		if(y>25)y=24;
		this.setTaille(new Coord(x,y));
		this.generation(proba,getTaille().x,getTaille().y);
	}
	

	@Override
	public void generation(int probaObstacle,int x, int y){
		this.map=new Map(x,y,probaObstacle);

	}



	public String printMatrix(){
		StringBuilder sb = new StringBuilder();
		Formatter formatter = new Formatter(sb, Locale.FRENCH);
		String formatS = "%1$9s";
		String[] valueTab = new String[taille.y+1];
		valueTab[0]="";
		for (int index = 0; index < taille.y; index++) {
			formatS = formatS + " %" + (index + 2) + "$9s";
			valueTab[index+1] = String.valueOf(index);
		}
		formatter.format(formatS + "\n", valueTab);
		formatter.format("%1$9s | %2$47s\n", "","_______________________________________________");
		for (int i = 0; i < taille.x; i++) {
			String formatS2 = "%1$9s | ";
			String[] valueTab2 = new String[taille.y+1];
			valueTab2[0]=String.valueOf(i);
			for (int j = 0; j < taille.y; j++) {
				formatS2 = formatS2 + " %" + (j + 2) + "$9s";
				valueTab2[j+1] =map.getTerrain()[i][j].getType().toString();
			}
			formatter.format(formatS2 + "\n", valueTab2);
		}
		return formatter.toString() ;
		}

	
	@Override
	public TypeCase contenuCase(Coord coord) {
		TypeCase ret=TypeCase.vide;
		ret=this.map.contenuCase(coord);
		return ret;
	}
	

	
	public boolean isObstacleHere(int i, int y) {
		boolean ret=false;
		if(i>= this.getTaille().x ||y >= this.getTaille().y ||i <0 ||y<0)
			ret=true;
		else{
			if (this.contenuCase(new Coord(i,y))==TypeCase.obstacle)
				ret=true;
		}

		return ret;
	}


	
	//getters et setters
	public Coord getTaille() {
		return taille;
	}


	public void setTaille(Coord taille) {
		this.taille = taille;
	}
	
	public Map getMap() {
		return map;
	}


	public void setMap(Map map) {
		this.map = map;
	}






}


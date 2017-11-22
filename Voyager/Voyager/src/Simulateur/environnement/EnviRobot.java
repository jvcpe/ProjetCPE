package Simulateur.environnement;

import java.util.Formatter;
import java.util.Locale;

import Simulateur.Coord;

public class EnviRobot extends AbstractEnvi{



	private Map map;
	private Coord taille;

	public EnviRobot(int x, int y){
		if(x<5)x=6;
		if(y<5)y=6;
		if(x>25)x=24;
		if(y>25)y=24;
		this.taille=new Coord(x,y);
		this.generation(0,taille.x,taille.y);
	}


	@Override
	public void generation(int proba, int x,int y){
		this.map=new Map();
		for(int i=0;i<x;i++)
		{
			for(int j=0;j<y;j++)
			{
				this.map.getTerrain()[i][j]=new Case(TypeCase.inconnue);
			}
		}

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


	public String matrixForJson(){
		String matrix="[";
		for(int i=0;i<this.taille.x;i++)
		{
			matrix+="[";
			for(int j=0;j<this.taille.y;j++)
			{
				switch(this.map.contenuCase(new Coord(i,j))){
				case obstacle:
					matrix += 2+",";
					break;

				case inconnue:
					matrix += 4+",";
					break;
				default:
					matrix+=1+",";
					break;
				}

			}
			matrix= matrix.substring(0, matrix.length()-1);
			matrix+="],";
		}
		matrix= matrix.substring(0, matrix.length()-1);
		matrix+="]";

		return matrix;


	}

	@Override
	public TypeCase contenuCase(Coord coord) {
		TypeCase ret=TypeCase.vide;
		ret=this.map.contenuCase(coord);
		return ret;
	}





	//getters et setters
	public Map getMap() {
		return map;
	}


	public void setMap(Map map) {
		this.map = map;
	}


	public Coord getTaille() {
		return taille;
	}


	public void setTaille(Coord taille) {
		this.taille = taille;
	}


}

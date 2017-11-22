package Simulateur.controleur;

import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import Simulateur.Coord;
import Simulateur.environnement.Case;
import Simulateur.environnement.EnviDev;
import Simulateur.environnement.TypeCase;
import Simulateur.mesures.Mesures;
import Simulateur.robot.Orientation;
import Simulateur.robot.Robot;

public class RobotCrt {


	private EnviDev environnement;
	private Robot robot;
	private Mesures mesures;
	private List<Coord> casesVisitees;




	public RobotCrt(EnviDev environnement, Robot robot) {
		this.robot = robot;
		this.environnement = environnement;
		this.mesures=new Mesures();
		this.casesVisitees=new LinkedList<Coord>();
		this.environnement.getMap().setCase(this.robot.getCoord(),new Case(TypeCase.vide));
		applicationPattern();
	}


	public void applicationPattern(){
		Coord coordCase;
		int cptObstaclesVisibles=0;
		//assert(this.environnement.getTaille().x <= 6 || this.environnement.getTaille().y <=6);
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				coordCase=new Coord(i,j);

				if(robot.getVision().getMatrice()[coordCase.x][coordCase.y]==1|| robot.getVision().getMatrice()[coordCase.x][coordCase.y]==2){
					coordCase=conversion(coordCase);
					if(coordCase.x >= this.getEnvironnement().getTaille().x ||coordCase.y >= this.getEnvironnement().getTaille().y ||coordCase.x <0 ||coordCase.y<0){
						//System.out.println("t'es nul");
					}
					else
					{
						TypeCase type=this.environnement.getMap().getTerrain()[coordCase.x][coordCase.y].getType();
						this.robot.getEnvironnement().getMap().setCase(coordCase,new Case(type));
						if(type==TypeCase.obstacle)
							cptObstaclesVisibles++;
					}
				}
			}
		}

		this.mesures.obstaclesVisiblesMaj(cptObstaclesVisibles);

	}

	public Coord conversion(Coord coordCasePatern){
		int x=coordCasePatern.x-2;
		int y=coordCasePatern.y-2;

		Coord coordEquivEnv=new Coord((robot.getCoord().x)+x , (robot.getCoord().y)+y);

		return coordEquivEnv;
	}



	public void deplacementRobot(String choix) {
		switch (choix) {
		case "UP":
			if(!environnement.isObstacleHere(robot.getCoord().x-1 , robot.getCoord().y)){
				this.casesVisitees.add(this.robot.getCoord());
				this.modifOrientation(Orientation.N);
				this.robot.deplacement(robot.getCoord().x-1, robot.getCoord().y);
				this.mesures.upgradeDistanceParcourue();
			}

			break;
		case "DOWN":
			if(!environnement.isObstacleHere(robot.getCoord().x+1, robot.getCoord().y)){
				this.casesVisitees.add(this.robot.getCoord());
				this.modifOrientation(Orientation.S);
				this.robot.deplacement(robot.getCoord().x+1 , robot.getCoord().y);
				this.mesures.upgradeDistanceParcourue();
			}
			break;
		case "LEFT":
			if(!environnement.isObstacleHere(robot.getCoord().x, robot.getCoord().y-1)){
				this.casesVisitees.add(this.robot.getCoord());
				this.modifOrientation(Orientation.O);
				this.robot.deplacement(robot.getCoord().x, robot.getCoord().y-1);
				this.mesures.upgradeDistanceParcourue();
			}
			break;
		case "RIGHT":
			if(!environnement.isObstacleHere(robot.getCoord().x, robot.getCoord().y+1)){
				this.casesVisitees.add(this.robot.getCoord());
				this.modifOrientation(Orientation.E);
				this.robot.deplacement(robot.getCoord().x, robot.getCoord().y+1);
				this.mesures.upgradeDistanceParcourue();
			}
			break;

		}
		this.mesures.upgradeCommande();
		this.applicationPattern();
		this.mesures.obstaclesRencontresMaj(this.robot.getEnvironnement());
		if(this.compareMaps())
		{
			System.out.println("Map découverte!");

		}

	}


	public void deplacementAuto(){
		boolean stop=false;
		double temp = -1;
		while(!stop){

			temp=Math.random();

			if(temp > (0.75)){
				this.deplacementRobot("UP");
			}
			else{
				if(temp>0.5){
					this.deplacementRobot("RIGHT");
				}

				else{
					if(temp>0.25){
						this.deplacementRobot("DOWN");
					}

					else{
						if(temp>0){
							this.deplacementRobot("LEFT");
						}
						else
							System.out.println("erreur fatale du deplacement random");
					}
				}
			}

			if(this.compareMaps())
			{
				stop=true;
				System.out.println("Map découverte!");

			}
		}
	}

	public boolean compareMaps(){
		boolean ret=true;
		for(int i=0;i<this.environnement.getTaille().x;i++)
		{
			for(int j=0;j<this.environnement.getTaille().y;j++)
			{
				if(this.environnement.contenuCase(new Coord(i,j))!=this.robot.getEnvironnement().contenuCase(new Coord(i,j))){
					ret=false;
				}

			}

		}
		return ret;
	}

	//Fonction de decouverte map optimisée
	/*
	 * chercher dans une boucle une case inconnue
	 * appeler fonction atteindre case
	 * cette fonction compare les coordonnees position destination et en deduit comment y aller a peu pres (tres gauche un peu haut par exemple)
	 * dans une boucle on deplace vers gauche tant que c'est possible, a chauqe fois que c'est impossible on va vers haut puis repart a gauche et ce jusqu'a ce que l'on atteigne la case
	 * si au bout d'un certain nombre d'occurence de boucle on a pas trouvé la case on suppose qu'on l'a louppé et on quitte la boucle et reverife notre position et celle du robot puis recommence la meme operation
	 * le tout dans une boucle qui se termine quand on a decouvert tout (comparMap() )
	 * 
	 */




	//Mesures
	public int getObstaclesVisibles(){
		return this.mesures.getNbObstaclesVisibles();
	}

	public void modifOrientation(Orientation ori){
		this.robot.setOrient(ori);
	}



	//Creation de fichier JSON a envoyer


	//getters et setters
	public EnviDev getEnvironnement() {
		return environnement;
	}



	public void setEnvironnement(EnviDev environnement) {
		this.environnement = environnement;
	}



	public Robot getRobot() {
		return robot;
	}



	public void setRobot(Robot robot) {
		this.robot = robot;
	}

	public List<Coord> getCasesVisitees() {
		return casesVisitees;
	}

	public String affichageCasesVisitee(){

		String ret="[";
		for(int i=0;i<this.environnement.getTaille().x;i++)
		{
			ret+="[";
			for(int j=0;j<this.environnement.getTaille().y;j++)
			{

				if(this.casesVisitees.contains(new Coord(i,j)))
					ret+=1+",";

				else
					ret +=0 +","; 
			}
			ret= ret.substring(0, ret.length()-1);
			ret+="],";
		}
		ret= ret.substring(0, ret.length()-1);
		ret+="]";


		return ret;
	}


	public void setCasesVisitees(List<Coord> casesVisitees) {
		this.casesVisitees = casesVisitees;
	}

	public Mesures getMesures() {
		return mesures;
	}


	public void setMesures(Mesures mesures) {
		this.mesures = mesures;
	}

}


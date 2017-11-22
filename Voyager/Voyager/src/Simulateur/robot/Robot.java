package Simulateur.robot;

import Simulateur.Coord;
import Simulateur.environnement.Case;
import Simulateur.environnement.EnviRobot;
import Simulateur.environnement.TypeCase;

public class Robot {

	private Coord coord;

	private Orientation orient;
	
	private EnviRobot environnement;

	private VisionPattern vision;

	//default constructor
	public Robot(int mapx,int mapy){
		this.coord=new Coord(0,0);
		this.orient = Orientation.N;
		this.environnement=new EnviRobot(mapx,mapy);
		this.vision=new VisionPattern();
	}

	//parameter constructor
	public Robot(int mapx, int mapy, int posInitX, int posInitY, Orientation orientInit){
		if(posInitX>=mapx)
			posInitX=0;
		
		if(posInitY>=mapy)
			posInitY=0;
		this.coord = new Coord(posInitX,posInitY);
		

		if(orientInit.equals(Orientation.N) || orientInit.equals(Orientation.O) || orientInit.equals(Orientation.E) || orientInit.equals(Orientation.S)){
			this.orient = orientInit;
		}
		else{
			this.orient = Orientation.N;
		}
		this.environnement=new EnviRobot(mapx,mapy);
		this.vision=new VisionPattern();
		this.vision.rotationPattern(this.orient);
		
	}

	//getters and setters


	public Orientation getOrient() {
		return orient;
	}

	public void setOrient(Orientation orient) {
		this.orient = orient;
		this.vision.rotationPattern(this.orient);
	}


	public Coord getCoord() {
		return coord;
	}

	public void setCoord(Coord coord) {
		this.coord = coord;
	}




	public EnviRobot getEnvironnement() {
		return environnement;
	}

	public void setEnvironnement(EnviRobot environnement) {
		this.environnement = environnement;
	}

	public VisionPattern getVision() {
		return vision;
	}

	public void setVision(VisionPattern vision) {
		this.vision = vision;
	}


	public void deplacement(int i, int y) {
		this.setCoord(new Coord(i,y));

	}





}

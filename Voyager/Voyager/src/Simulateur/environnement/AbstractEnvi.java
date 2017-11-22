package Simulateur.environnement;

import Simulateur.Coord;

public abstract class AbstractEnvi {


	public abstract void generation(int probaObstacle,int x, int y);


	public abstract String printMatrix();
		

	public abstract TypeCase contenuCase(Coord coord);






}



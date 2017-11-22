package Simulateur.robot;

public class VisionPattern {
	
	private int[][] matrice;

	

	//default constructor
	public VisionPattern(){
		creationPattern();
	}
	
	public int[][] getMatrice() {
		return matrice;
	}


	public void setMatrice(int[][] matrice) {
		this.matrice = matrice;
	}

	public void creationPattern(){
		this.matrice=new int[5][5];

		matrice[0][2]=1;
		
		matrice[1][1]=1;
		matrice[1][2]=1;
		matrice[1][3]=1;
		
		matrice[2][1]=1;
		matrice[2][2]=2;
		matrice[2][3]=1;
		
		matrice[3][2]=1;
	
	}

	public void afficherPattern(){
		int i, j;
		for(i=0; i<matrice.length; i++) {
			for(j=0; j<matrice[i].length; j++) {
				System.out.print(matrice[i][j]+ "\t");
			}
			System.out.println("");
		}
	}



	public void transpose() {

		for (int i = 0; i < matrice.length; i++) {
			for (int j = i; j < matrice[0].length; j++) {
				int x = matrice[i][j];
				matrice[i][j] = matrice[j][i];
				matrice[j][i] = x;
			}
		}
	
	}

	public void rotateByNinetyToLeft() {
		// transpose
		this.transpose();

		//  swap rows
		for (int  i = 0; i < matrice.length/2; i++) {
			for (int j = 0; j < matrice[0].length; j++) {
				int x = matrice[i][j];
				matrice[i][j] = matrice[matrice.length -1 -i][j]; 
				matrice[matrice.length -1 -i][j] = x;
			}
		}
	}


	public void rotateByNinetyToRight() {
		// transpose
		transpose();

		// swap columns
		for (int  j = 0; j < matrice[0].length/2; j++) {
			for (int i = 0; i < matrice.length; i++) {
				int x = matrice[i][j];
				matrice[i][j] = matrice[i][matrice[0].length -1 -j]; 
				matrice[i][matrice[0].length -1 -j] = x;
			}
		}
	}

	public void rotationPattern( Orientation orientRobot){
		this.creationPattern();

		switch (orientRobot) {
		case O:  rotateByNinetyToLeft();
		break;
		case E:  rotateByNinetyToRight();
		break;
		case S: rotateByNinetyToRight();
				rotateByNinetyToRight();
		break;
		default:
			break;
		}        


	}



}

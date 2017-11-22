package model;

public class PieceIHM implements Pieces{

	@Override
	public int getX() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int getY() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public Couleur getCouleur() {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public String getName() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean isMoveOk(int xFinal, int yFinal, boolean isCatchOk, boolean isCastlingPossible) {
		// TODO Auto-generated method stub
		return false;
	}

	public String toString() {
		String string = "string";
		return string;
	}

	@Override
	public boolean move(int xFinal, int yFinal) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean capture() {
		// TODO Auto-generated method stub
		return false;
	}


	public Object getList() {
		// TODO Auto-generated method stub
		return null;
	}

	public String getTypePiece() {
		// TODO Auto-generated method stub
		return null;
	}
	


}

package Simulateur.environnement;

public class Case {
	


	private TypeCase type; 
	
	public Case(TypeCase type){
		this.type=type;
	}
	
	
	public TypeCase getType() {
		return type;
	}

	public void setType(TypeCase type) {
		this.type = type;
	}
}

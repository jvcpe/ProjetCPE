package ProjetInfo_JEE.model;


import java.io.Serializable;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;

import Simulateur.controleur.RobotCrt;

@ManagedBean
@RequestScoped

public class LoginBean implements Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String login;
	private String pwd;
	private int largeur;
	private int proba;

	

	public int getProba() {
		return proba;
	}
	public void setProba(int proba) {
		this.proba = proba;
	}
	public String getLogin() {return login;}
	public void setLogin(String login) {this.login = login;}
	public String getPwd() {return pwd;}
	public void setPwd(String pwd) {this.pwd = pwd;}
	
	public int getLargeur() {return largeur;}
	public void setLargeur(int largeur) {this.largeur = largeur;}
}
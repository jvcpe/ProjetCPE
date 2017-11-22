package Securite;

import java.io.IOException;

import javax.faces.context.FacesContext;

import ProjetInfo_JEE.model.UserModelBean;
import ProjetInfo_JEE.model.UserSubmissionModelBean;

public class Securite {
	
	private String login;
	private String pwd;
	private boolean telecommande;
	
	public Securite(String login, String pwd)
	{
		this.telecommande=true;
		this.login=login;
		this.pwd=pwd;
	}
	
public static Securite user=new Securite("Start","Start");
	

public String getLogin() {
	return this.login;}
public void setLogin(String login) {
	this.login = login;}
public String getPwd() {
	return this.pwd;}
public void setDeplacement(String pwd) {
	this.pwd = pwd;}
public boolean getTelecommande() {
	return telecommande;}
public void setTellecommande(boolean tel) {
	this.telecommande = tel;}




public static void DefineUser(UserModelBean userSubmitted){
	
		user.login=userSubmitted.getLogin();
		user.pwd=userSubmitted.getPwd();
		
	}

public static void SwitchTel()
{
	if(user.telecommande == true)
	{
		user.telecommande = false;
		System.out.println(user.telecommande);
	}
	else
	{
		user.telecommande = true;
		System.out.println(user.telecommande);
	}
}

public static boolean CheckTel()
{

	return(user.telecommande);
	
}

public static void deconnexion()
{
	user.login = "Start";
	user.pwd = "Start";
	System.out.println("Systeme libre");
	
}

public static void deconnexionAdmin()
{
	System.out.println("DeconnexionAdmin");	
}
public static boolean CompareUser(UserModelBean userSubmitted)
{
	if( (user.login== userSubmitted.getLogin() && user.pwd == userSubmitted.getPwd()) 
			|| (user.login == "Start" && user.pwd == "Start"))
	{
		DefineUser(userSubmitted);
		return true;
	}
	else
	{
		System.out.println("En cours d utilisation par un autre utilisateur");
		return false;
	}
}
}

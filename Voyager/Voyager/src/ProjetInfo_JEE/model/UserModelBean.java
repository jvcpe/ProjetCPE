package ProjetInfo_JEE.model;

import java.io.Serializable;

import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

@ManagedBean
@SessionScoped 
//contrainte BEAN implements Serializable
public class UserModelBean implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String login;
	private String pwd;



	//Contrainte BEAN constructeur sans paramètre
	public UserModelBean() {
	}
	
	
	public UserModelBean(String login,String pwd)
	{
		this.login = login;
		this.pwd = pwd;
	}

	public String getLogin() {return login;}
	public void setLogin(String login) {this.login = login;}
	public String getPwd() {return pwd;}
	public void setPwd(String pwd) {this.pwd = pwd;}
	@Override
	public String toString() {
		return
				"[LOGIN]:"+this.getLogin()+",[PWD]:"+this.getPwd();
	}
}

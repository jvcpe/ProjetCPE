package ProjetInfo_JEE.model;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;

@ManagedBean
@RequestScoped //Durée de vue uniquement lors d'une requète
//même propriétés que UserModelBean mais portée différente
public class UserSubmissionModelBean extends UserModelBean{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * 
	 */
	private String login;
	private String pwd;
	//Contrainte BEAN constructeur sans paramètre
	public UserSubmissionModelBean() {
	}
	
	public UserSubmissionModelBean(String login,String pwd)
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
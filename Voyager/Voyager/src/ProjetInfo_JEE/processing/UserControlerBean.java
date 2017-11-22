package ProjetInfo_JEE.processing;


import java.io.IOException;
import java.util.Map;

import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.faces.context.ExternalContext;
import javax.faces.context.FacesContext;



import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.rest.services.LargeurMap;
import com.rest.services.RobotControlService;

import ProjetInfo_JEE.DAO.DaoFabric;
import ProjetInfo_JEE.DAO.UserDao;
import ProjetInfo_JEE.model.LoginBean;
import ProjetInfo_JEE.model.RobotBean;
import ProjetInfo_JEE.model.UserModelBean;
import ProjetInfo_JEE.model.UserSubmissionModelBean;
import Simulateur.controleur.RobotCrt;
import Simulateur.environnement.EnviDev;
import Simulateur.robot.Orientation;
import Simulateur.robot.Robot;
import Securite.Securite;

@WebServlet("/CheckAuth")
@ManagedBean
@ApplicationScoped // Utilisation de application scope afin d'offrir un point d'entrée unique à l'ensemble des clients
public class UserControlerBean {
	private UserDao userDao;
	public UserControlerBean() {
		this.userDao=DaoFabric.getInstance().createUserDao();	
	}
	public String checkUser(LoginBean loginBean){
		UserModelBean user = this.userDao.checkUser(loginBean.getLogin(),
				loginBean.getPwd());
		UserModelBean admin = this.userDao.checkAdmin(loginBean.getLogin(),
				loginBean.getPwd());
		LargeurMap.largeur=loginBean.getLargeur();
		LargeurMap.proba=loginBean.getProba();
	
		
		if( admin!=null){
			//récupère l'espace de mémoire de JSF
			ExternalContext externalContext =
					FacesContext.getCurrentInstance().getExternalContext();
			Map<String, Object> sessionMap = externalContext.getSessionMap();
			//place l'utilisateur dans l'espace de mémoire de JSF
			sessionMap.put("loggedUser", user);
			//redirect the current page
		
				try {
					FacesContext.getCurrentInstance().getExternalContext()
					.redirect("http://localhost:8080/Projet_Info_Annee4/admin.html");
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		     return "userLogin.xhtml";
		}
		
		
		if( user!=null){
			//récupère l'espace de mémoire de JSF
			ExternalContext externalContext =
					FacesContext.getCurrentInstance().getExternalContext();
			Map<String, Object> sessionMap = externalContext.getSessionMap();
			//place l'utilisateur dans l'espace de mémoire de JSF
			sessionMap.put("loggedUser", user);
			//redirect the current page
			
			if(Securite.CompareUser(user) == true)
			{
				try {
					FacesContext.getCurrentInstance().getExternalContext()
					.redirect("http://localhost:8080/Projet_Info_Annee4/cmd2.html");
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				return "redirection";
			}
			return "userLogin.xhtml";
			
			
		}else{
			//redirect the current page
			return "userLogin.xhtml";
		}
		
	}
	
	public void checkAndAddUser(UserSubmissionModelBean userSubmitted){
		
		UserModelBean user = this.userDao.checkUser(userSubmitted.getLogin(),userSubmitted.getPwd());
		//Vérifier les propriétés de l'utilisateur
		if (user==null ) 
		//ajout de l'utilisateur à la base de données
		 this.userDao.addUser(userSubmitted);
	}

	
}



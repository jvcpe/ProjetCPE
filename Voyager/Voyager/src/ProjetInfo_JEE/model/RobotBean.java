package ProjetInfo_JEE.model;


import java.io.Serializable;

import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;

import Simulateur.controleur.RobotCrt;

@ManagedBean
@ApplicationScoped
public class RobotBean implements Serializable{
	private static final long serialVersionUID = 1L;
	private RobotCrt robotCrt;

		public RobotBean(RobotCrt robotCrt2) {
		this.robotCrt=robotCrt2;
	}
		public RobotCrt getRobotCrt() {
		return robotCrt;
	}
	public void setRobotCrt(RobotCrt robotCrt) {
		this.robotCrt = robotCrt;
	}
		
}

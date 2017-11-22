package com.rest.services;

import java.io.FileWriter;
import java.io.IOException;

import javax.annotation.PostConstruct;
import javax.faces.bean.ApplicationScoped;
import javax.servlet.ServletContext;
import javax.ws.rs.ApplicationPath;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import ProjetInfo_JEE.model.LoginBean;
import ProjetInfo_JEE.model.RobotBean;
import Simulateur.controleur.RobotCrt;
import Simulateur.environnement.EnviDev;
import Simulateur.robot.Orientation;
import Simulateur.robot.Robot;
import Securite.Securite;


@Path("/cmd")
public class RobotControlService {
	private final static String ROBOT_SIMULATOR_LABEL="robot_simulator";

	//Inject servlet context (needed to get general context, application memory space, session memory space ...)
	@Context
	ServletContext context;

	//After RestService construction launches init method
	@PostConstruct
	public void init(){
		
		checkRobot();
	}

	private void checkRobot() {
		Object obj=context.getAttribute(ROBOT_SIMULATOR_LABEL);
	}
	
	@POST
	@Produces(MediaType.APPLICATION_JSON)
	@Path("gen")
	public String generation()
	{
		
		context.setAttribute("ROBOT",new RobotBean(new RobotCrt(new EnviDev(LargeurMap.proba, LargeurMap.largeur,LargeurMap.largeur),new Robot(LargeurMap.largeur,LargeurMap.largeur, 3,2,Orientation.S) )));
		return this.getEnv();
	}

	
	@POST
	@Produces(MediaType.APPLICATION_JSON)
	@Path("DOWN")
	public String goDown()
	{
		if(Securite.CheckTel() == true)
		{
			( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).deplacementRobot("DOWN");
			return this.getEnv();
		}
		System.out.println("Un administrateur a interdit l'accès au robot");
		return "Un administrateur a interdit l'accès au robot";
	}

	
	@POST
	@Produces(MediaType.APPLICATION_JSON)
	@Path("UP")
	public String goUp()
	{
		if(Securite.CheckTel() == true)
		{
			( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).deplacementRobot("UP");
			return this.getEnv();
		}
		System.out.println("Un administrateur a interdit l'accès au robot");
		return "Un administrateur a interdit l'accès au robot";
	}

	
	
	@POST
	@Produces(MediaType.APPLICATION_JSON)
	@Path("LEFT")
	public String goLeft()
	{
		if(Securite.CheckTel() == true)
		{
			( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).deplacementRobot("LEFT");
			return this.getEnv();
		}
		System.out.println("Un administrateur a interdit l'accès au robot");
		return "Un administrateur a interdit l'accès au robot";
	}
	
	@POST
	@Produces(MediaType.APPLICATION_JSON)
	@Path("RIGHT")
	public String goRight()
	{
		if(Securite.CheckTel() == true)
		{
			( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).deplacementRobot("RIGHT");
			return this.getEnv();
		}
		System.out.println("Un administrateur a interdit l'accès au robot");
		return "Un administrateur a interdit l'accès au robot";
	}
	
	
	@POST
	@Produces(MediaType.TEXT_PLAIN)
	@Path("comp")
	public boolean compareMaps()
	{
		
		return ( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt().compareMaps());
	}
	
	
	@POST
	@Produces(MediaType.APPLICATION_JSON)
	@Path("TELECOMMANDE")
	public void tell()
	{
		Securite.SwitchTel();
	}
	
	@POST
	@Produces(MediaType.APPLICATION_JSON)
	@Path("DECONNEXION")
	public void deconnexion()
	{
		Securite.deconnexion();
	}
	
	@POST
	@Produces(MediaType.APPLICATION_JSON)
	@Path("DECONNEXIONADMIN")
	public void deconnexionAdmin()
	{
		Securite.deconnexionAdmin();
	}
	
	
	
	
	@GET
	@Produces(MediaType.APPLICATION_JSON)
	@Path("env")
	public String getEnv()
	{
		String ret=null;
		//create Json container Object
		JSONObject objContainer = new JSONObject();

		//create set of json objects
		JSONObject position = new JSONObject();
		position.put("orientation",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getRobot().getOrient().toString());
		position.put("hauteurMap",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getEnvironnement().getTaille().x);
		position.put("largeurMap",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getEnvironnement().getTaille().y);
		position.put("x",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getRobot().getCoord().x);
		position.put("y", ( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getRobot().getCoord().y);

		JSONObject dataCapteur = new JSONObject();
		dataCapteur.put("hauteurPattern",new Integer(5));
		dataCapteur.put("largeurPattern",new Integer(5));

		JSONObject dataMap = new JSONObject();
		dataMap.put("map",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getRobot().getEnvironnement().matrixForJson());
		dataMap.put("mapVisitee",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).affichageCasesVisitee());

		JSONObject mesures = new JSONObject();
		mesures.put("nbCommandes",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getMesures().getNbCommandes());
		mesures.put("nbObstaclesVisibles",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getMesures().getNbObstaclesVisibles());
		mesures.put("nbObstaclesRencontres",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getMesures().getNbObstaclesRencontres());
		mesures.put("distanceParcourue",( ((RobotBean) context.getAttribute("ROBOT")).getRobotCrt()).getMesures().getDistanceParcourue());

		//create a json list
		JSONArray list = new JSONArray();
		//add json objects to jsonlist
		list.add(position);
		list.add(dataCapteur);
		list.add(dataMap);
		list.add(mesures);

		//add jsonlist to json container
		objContainer.put("robot", list);

		try (FileWriter file = new FileWriter("/fs03/share/users/loic.blanchard/home/test.json")) {
			ret=objContainer.toJSONString();
			//code degueu du turfu permettant de virer des accolades indésirables mammen
			String ret1= ret.substring(0, ret.indexOf("mapVisitee")+12);
			String ret2= ret.substring(ret.indexOf("mapVisitee")+13,ret.length());
			ret=ret1+ret2;
			ret1= ret.substring(0, ret.indexOf("map\"")-3);
			ret2= ret.substring(ret.indexOf("map\"")-2,ret.length());
			ret=ret1+ret2;
			ret1= ret.substring(0, ret.indexOf("map\"")+5);
			ret2= ret.substring(ret.indexOf("map\"")+6,ret.length());
			ret=ret1+ret2;
			ret1= ret.substring(0, ret.indexOf("distanceParcourue")-5);
			ret2= ret.substring(ret.indexOf("distanceParcourue")-4,ret.length());
			ret=ret1+ret2;
			file.write(ret);
			file.flush();

		} catch (IOException e) {
			e.printStackTrace();
		}

		//return json string of the json container
		return ret;





		//ALTERNATIVE send direct a json String
		//return "{\"data\":[{\"x\":0,\"y\":0,\"val\":\"FREE\"},{\"x\":0,\"y\":1,\"val\":\"WALL\"},{\"x\":1,\"y\":1,\"val\":\"ROBOT\"}]}";
	}

}

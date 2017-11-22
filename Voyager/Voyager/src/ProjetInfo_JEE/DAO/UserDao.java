package ProjetInfo_JEE.DAO;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import ProjetInfo_JEE.model.UserModelBean;

import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class UserDao {
	private Connection connection;
	private String dB_HOST;
	private String dB_PORT;
	private String dB_NAME;
	private String dB_USER;
	private String dB_PWD;
	public UserDao(String DB_HOST,String DB_PORT, String DB_NAME,String DB_USER,String
			DB_PWD) {
		dB_HOST = DB_HOST;
		dB_PORT = DB_PORT;
		dB_NAME = DB_NAME;
		dB_USER = DB_USER;
		dB_PWD = DB_PWD;
	}
	
	public void addUser(UserModelBean user) {

		try {
			connection = java.sql.DriverManager.getConnection("jdbc:mysql://"+ dB_HOST + ":" + dB_PORT + "/" + dB_NAME, dB_USER, dB_PWD);

			java.sql.PreparedStatement query =(PreparedStatement) connection.prepareStatement("INSERT INTO user(login, pwd) VALUES (?,?);");
			
			query.setString(1,user.getLogin());
			query.setString(2,user.getPwd());
			
			System.out.println(query);
			
			query.executeUpdate();
			
			/*java.sql.Statement st=connection.createStatement();
			st.executeUpdate("INSERT INTO public.users (login, pwd) VALUES ('"+user.getLogin()+"','"+user.getPwd()+"');");*/
			

			connection.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public ArrayList<UserModelBean> getAllUser(){

		ArrayList<UserModelBean> userList=new ArrayList<UserModelBean>();
		try {

			connection = java.sql.DriverManager.getConnection("jdbc:mysql://"
					+ dB_HOST + ":" + dB_PORT + "/" + dB_NAME, dB_USER, dB_PWD);

			PreparedStatement querySt = (PreparedStatement) connection.prepareStatement("Select * from user");

			ResultSet rst=querySt.executeQuery();
			while(rst.next()){
				UserModelBean user=new UserModelBean((rst.getString("login")),rst.getString("pwd"));
				userList.add(user);
			}
			
			rst.close();
			querySt.close();
			connection.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return userList;
	}

	public UserModelBean checkUser(String login, String pwd) {
		UserModelBean userChck = null;

		try{

			connection = java.sql.DriverManager.getConnection("jdbc:mysql://"+ dB_HOST + ":" + dB_PORT + "/" + dB_NAME, dB_USER, dB_PWD);

			PreparedStatement	 querySt = (PreparedStatement) connection.prepareStatement("Select * from user where login=? && pwd=?");
			querySt.setString(1, login);
			querySt.setString(2, pwd);

			ResultSet rst=querySt.executeQuery();
			while(rst.next()){
				userChck=new UserModelBean(rst.getString("login"),rst.getString("pwd"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return userChck;
	}
	
	public UserModelBean checkAdmin(String login, String pwd) {
		UserModelBean userChck = null;

		try{

			connection = java.sql.DriverManager.getConnection("jdbc:mysql://"+ dB_HOST + ":" + dB_PORT + "/" + dB_NAME, dB_USER, dB_PWD);

			PreparedStatement	 querySt = (PreparedStatement) connection.prepareStatement("Select * from Admin where pwd=? && login=?");
			querySt.setString(1, pwd);
			querySt.setString(2, login);

			ResultSet rst=querySt.executeQuery();
			while(rst.next()){
				userChck=new UserModelBean(rst.getString("login"),rst.getString("pwd"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return userChck;
	}
	
	public static void main (String[] args){
		

	}

}

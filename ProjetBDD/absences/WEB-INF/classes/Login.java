import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet{

	public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		/* En-tête */
		out.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" ><head>       <title>Accueil</title>       <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />	   <link rel=\"stylesheet\" media=\"screen\" type=\"text/css\" title=\"Design\" href=\"../styles/design.css\" />   </head>   <body>");
		/* Fin de l'en-tête */
		String url="jdbc:odbc:absences";
		String nom="";
		String mdp="";
		String logine=req.getParameter("login");
		String passworde=req.getParameter("password");
		/* Connexion à la BDD */
		try{
			// enregistrement du driver
			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
			Connection con = DriverManager.getConnection(url,nom,mdp);
			Statement stmt = con.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM utilisateurs WHERE login='"+logine+"'");
			if(rs.next()){
				if(rs.getString("password").equals(passworde)){
					session.putValue("login",logine);
					con.close();
					res.sendRedirect("Accueil");
				}
				
			}
			out.println("<p> Login/Mot de passe incorrect(s) !! </p>");
			out.println("<a href=\"../index.html\">Retour</a>");
			
			// fermeture des espaces
			con.close();
		}
		catch(Exception e){
			out.println("Erreur connexion base de données");
		}
		
		
		/* Fin du fichier HTML */
		out.println("</body");
		out.println("</html>");
	}

}
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;


/**
	Ce fichier redirige juste l'enseignant ou le secrétaire vers la fiche de détail de l'étudiant choisi
*/
public class Saisie extends HttpServlet{

	public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		/* En-tête */
		out.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" ><head>       <title>Saisie des absences</title>       <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />	   <link rel=\"stylesheet\" media=\"screen\" type=\"text/css\" title=\"Design\" href=\"../styles/design.css\" />   </head>   <body>");
		/* Fin de l'en-tête */
		String url="jdbc:odbc:absences";
		String nom="";
		String mdp="";
		String logine=(String)session.getAttribute("login");
		
		/* Connexion à la BDD */
		try{
			// enregistrement du driver
			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
			Connection con = DriverManager.getConnection(url,nom,mdp);
		
			Statement stmt = con.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM cours");
			out.println("<h1> Saisie d'une absence </h1>");
			if(req.getParameter("message") != null){
				out.println("<p>"+req.getParameter("message")+"</p>");
			}
			out.println("<form method=\"post\" action=\"SaisiePost\">");
			out.println("<p>");
			
			out.println("<label for=\"matiere\"> Matière </label><br/>");
			out.println("<select name=\"matiere\" size=\"1\">");
			while(rs.next()){
			// value = numéro du cours label = nom de la matière
				out.println("<option value=\""+rs.getInt(1)+"\">"+rs.getString(2)+"</option>");
			}
			out.println("</select>");
			out.println("</p>");
			out.println("<p><label> Etudiant : </label><input type=\"text\" name=\"login\" /></p>");
			out.println("<p><label> Date (format AAAA/MM/JJ) : </label><input type=\"text\" name=\"dateAbsence\"/></p>");
			out.println("<p><input type=\"submit\"/></p>");
			out.println("</form><br/>");
			out.println("<p><a href=\"Accueil\">Retour à l'accueil</a></p>");
			out.println("<p><a href=\"../index.html\">Se déconnecter</a></p>");
			
		}
		catch(Exception e){
			out.println("Erreur co' BDD"+e.getMessage());
		}
	}
}

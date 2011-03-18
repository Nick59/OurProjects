import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class ListeEtu extends HttpServlet{

	public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		/* En-tête */
		out.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" ><head>       <title>Liste des absences</title>       <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />	   <link rel=\"stylesheet\" media=\"screen\" type=\"text/css\" title=\"Design\" href=\"../styles/design.css\" />   </head>   <body>");
		/* Fin de l'en-tête */
		out.println("<h1> Liste des absences </h1>");
		String url="jdbc:odbc:absences";
		String nom="";
		String mdp="";
		String logine=(String)session.getAttribute("login");
		if(session.getAttribute("login")==null || session.getAttribute("login").equals("")){
			res.sendRedirect("../index.html");
		}
		/* Connexion à la BDD */
		try{
			// enregistrement du driver
			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
			Connection con = DriverManager.getConnection(url,nom,mdp);
			
			Statement stmt = con.createStatement();
			ResultSet etudiants = stmt.executeQuery("SELECT absences.etudiant, count(absences.etudiant) AS NombreAbsences FROM absences GROUP BY absences.etudiant ORDER BY count(absences.etudiant) DESC ");
			out.println("<table>");
			out.println("<tr>");
			out.println("<th> Nom de l'étudiant </th>");
			out.println("<th> Nombre d'absences </th>");
			out.println("</tr>");
				String nomEtu;
			while(etudiants.next()){
				nomEtu=etudiants.getString(1);
				out.println("<tr>");
				out.println("<td><a href=\"VersFicheEtu?nomEtu="+nomEtu+"\">"+nomEtu+"</a></td><td>" + etudiants.getInt(2)+"</td>");
				out.println("</tr>");
			}
			out.println("</table>");
			out.println("<p><a href=\"Accueil\">Retour à l'accueil</a></p>");
			out.println("<p><a href=\"../index.html\">Se déconnecter</a></p>");
			
		}
		catch(Exception e){
			out.println("Erreur co' BDD"+e.getMessage());
		}
	}
}
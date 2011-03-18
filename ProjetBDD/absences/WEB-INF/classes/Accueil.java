import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Accueil extends HttpServlet{

	public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		/* En-tête */
		out.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" ><head>       <title>Accueil</title>       <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />	   <link rel=\"stylesheet\" media=\"screen\" type=\"text/css\" title=\"Design\" href=\"../styles/design.css\" />   </head>   <body>");
		/* Fin de l'en-tête */
		out.println("<h1> Accueil </h1>");
		if(req.getParameter("message") != null){
			out.println("<p>"+req.getParameter("message")+"</p>");
		}
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
			ResultSet rs = stmt.executeQuery("SELECT * FROM utilisateurs WHERE login='"+logine+"'");
			int role=-1;
			if(rs.next()){
				role=rs.getInt("role");
				session.putValue("statut",role);
			}
			switch(role){
				case 0:
					session.putValue("nomEtu",logine);
					res.sendRedirect("FicheEtu");
				break;
					
				case 1:
					out.println("<p><a href=\"Justification\">Saisir un justificatif</a></p>");
					out.println("<p><a href=\"ListeEtu\">Voir la liste des etudiants</a></p>");
				break;
				
				case 2:
					out.println("<p><a href=\"Saisie\">Saisir une absence</a></p>");
					out.println("<p><a href=\"ListeEtu\">Voir la liste des etudiants</a></p>");
				break;
				
				default:
				out.println("<p>Erreur, reconnectez vous ou contactez l'administrateur</p>");
				break;
			}
			
			
			// fermeture des espaces
			con.close();
		}
		catch(Exception e){
			out.println("<p>Erreur connexion base de données</p>");
		}
		
		out.println("<p><a href=\"../index.html\">Se déconnecter</a></p>");
		/* Fin du fichier HTML */
		out.println("</body");
		out.println("</html>");
	}

}
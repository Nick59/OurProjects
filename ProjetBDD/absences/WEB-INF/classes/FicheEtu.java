import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class FicheEtu extends HttpServlet{

	public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		/* En-tête */
		out.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" ><head>       <title>Fiche Etudiant</title>       <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />	   <link rel=\"stylesheet\" media=\"screen\" type=\"text/css\" title=\"Design\" href=\"../styles/design.css\" />   </head>   <body>");
		/* Fin de l'en-tête */
		out.println("<h1> Fiche Etudiant </h1>");
		String url="jdbc:odbc:absences";
		String nom="";
		String mdp="";
		String etu=(String)session.getAttribute("nomEtu");
		if(session.getAttribute("login")==null || session.getAttribute("login").equals("")){
			res.sendRedirect("../index.html");
		}
		if(etu==null || etu.equals("")){
			res.sendRedirect("../index.html");
		}
		/* Connexion à la BDD */
		try{
			// enregistrement du driver
			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
			Connection con = DriverManager.getConnection(url,nom,mdp);
			Statement stmt = con.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM utilisateurs WHERE login='"+etu+"'");
			ResultSetMetaData rsmd = rs.getMetaData();
			Statement stmtCount = con.createStatement();
			ResultSet rsCount = stmtCount.executeQuery("SELECT count(*) FROM absences WHERE etudiant ='"+etu+"'");
			Statement stmtInju = con.createStatement();
			ResultSet rsInju = stmtInju.executeQuery("SELECT count(*) FROM absences WHERE etudiant ='"+etu+"' AND justification='non'");
			Statement stmtAbs = con.createStatement();
			ResultSet rsAbs = stmtAbs.executeQuery("SELECT * FROM absences WHERE etudiant ='"+etu+"'");
			int nbabsJustifiees=-1;
			int nbabs=-1;
			// nombre d'absences
			if(rsCount.next()){
				nbabs=rsCount.getInt(1);
			}
			
			// nombres d'absences injustifiees
			if(rsInju.next()){
				nbabsJustifiees=rsInju.getInt(1);
				nbabsJustifiees=nbabs-nbabsJustifiees;
			}
			
			// affichage
			if(rs.next()){
				out.println("<h2> Absences de l'étudiant(e) "+rs.getString("nom")+" "+rs.getString("prenom")+"</h2>");
				out.println("<h3>"+nbabs+" (dont "+nbabsJustifiees+" justifiée(s))</h3>");
				out.println("<table>");
				out.println("<tr>");
				out.println("<th> Date </th>");
				out.println("<th> Justification </th>");
				out.println("</tr>");
				while(rsAbs.next()){
					out.println("<tr>");
					// Microsoft Access donnant les dates avec l'heure, on ne garde que la date avec un substring
					out.println("<td> "+rsAbs.getString("dateAbs").substring(0,10)+"</td>");
					out.println("<td> "+rsAbs.getString("justification")+"</td>");
					out.println("</tr>");
				}
				out.println("</table>");
				out.println("<a href=\"../index.html\">Se déconnecter</a>");
				if(((Integer)session.getAttribute("statut"))>0){
					out.println("<p><a href=\"Accueil\">Retour à l'accueil</a></p>");
					out.println("<p><a href=\"ListeEtu\">Retour à la liste</a></p>");
				}
			}
		}
		catch(Exception e){
			out.println("Erreur co' BDD"+e.getMessage());
		}
	}
}
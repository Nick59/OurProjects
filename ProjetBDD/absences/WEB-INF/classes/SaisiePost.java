import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import java.util.regex.*;


/**
	Ce fichier redirige juste l'enseignant ou le secrétaire vers la fiche de détail de l'étudiant choisi
*/
public class SaisiePost extends HttpServlet{

	public Pattern pattern;
	public Matcher matcher;

	public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
	
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		/* En-tête */
		out.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" ><head>       <title>Chargement de la fiche etudiant</title>       <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />	   <link rel=\"stylesheet\" media=\"screen\" type=\"text/css\" title=\"Design\" href=\"../styles/design.css\" />   </head>   <body>");
		/* Fin de l'en-tête */
		out.println("<h1> Chargement de la fiche en cours... </h1>");
		String url="jdbc:odbc:absences";
		String nom="";
		String mdp="";
		String logine=(String)session.getAttribute("login");
		if(session.getAttribute("login")==null || session.getAttribute("login").equals("")){
			res.sendRedirect("../index.html");
		}
		pattern = Pattern.compile("^\\d{4}/\\d{2}/\\d{2}$");
		matcher = pattern.matcher(req.getParameter("dateAbsence"));
		/* Connexion à la BDD */
		try{
			// enregistrement du driver
			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
			Connection con = DriverManager.getConnection(url,nom,mdp);

			Statement stmt = con.createStatement();
			ResultSet rs=stmt.executeQuery("Select count(*) FROM utilisateurs WHERE login='"+req.getParameter("login")+"'");
			rs.next();
			if(rs.getInt(1) == 1){
				
				if(matcher.find()){
					//Insert une absence dans la base de données.
					int result = stmt.executeUpdate("INSERT INTO absences VALUES('"+req.getParameter("login")+"', "+req.getParameter("matiere")+",'Non','"+req.getParameter("dateAbsence")+"')");
					if(result != 0){
						//vers l'accueil
						res.sendRedirect("Accueil?message=L'absence%20a%20été%20ajoutée");
					}else{
						//vers le formulaire d'ajout d'absence avec un message d'erreur
						res.sendRedirect("Saisie?message=Erreur%20Base%20de%20données,%20contactez%20votre%20administrateur");
					}
				}
				else{
					res.sendRedirect("Accueil?message=Date%20Incorrecte");
				}
			
			}
			
			
		}
		catch(Exception e){
			out.println("<p>Erreur base de données </p>");
			out.println(e.getMessage());
		}
	}
}

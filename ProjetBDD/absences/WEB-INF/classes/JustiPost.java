import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import java.util.regex.*;


/**
	Ce fichier redirige juste l'enseignant ou le secrétaire vers la fiche de détail de l'étudiant choisi
*/
public class JustiPost extends HttpServlet{

	public Pattern pattern;
	public Matcher matcher;
	public Matcher matcher2;

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
		pattern = Pattern.compile("^\\d{2}/\\d{2}/\\d{4}$");
		matcher = pattern.matcher(req.getParameter("d1"));
		matcher2= pattern.matcher(req.getParameter("d2"));
		/* Connexion à la BDD */
		try{
			// enregistrement du driver
			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
			Connection con = DriverManager.getConnection(url,nom,mdp);

			Statement stmt = con.createStatement();
			ResultSet rs=stmt.executeQuery("Select count(*) FROM utilisateurs WHERE login='"+req.getParameter("login")+"'");
			rs.next();
			if(rs.getInt(1) == 1){
				
				if(matcher.find() && matcher2.find()){
					String update="UPDATE absences SET justification='"+req.getParameter("justificatif")+"' WHERE justification='Non' AND etudiant='"+req.getParameter("login")+"' AND dateAbs>=#"+req.getParameter("d1")+"# AND dateAbs<=#"+req.getParameter("d2")+"#";
					int result = stmt.executeUpdate(update);
					if(result != 0){
						//vers l'accueil
						res.sendRedirect("Accueil?message=Justification%20validée");
					}else{
						//vers le formulaire de justification avec un message d'erreur
						res.sendRedirect("Justification?message=Erreur%20Base%20de%20données,%20contactez%20votre%20administrateur%20"+update);
					}
				}
				else{
					res.sendRedirect("Accueil?message=Date%20Incorrecte");
				}
			
			}
			else{
				//vers le formulaire de justification
				res.sendRedirect("Justification?message=Erreur%20Base%20de%20données,%20contactez%20votre%20administrateur");
			}
			
			
		}
		catch(Exception e){
			out.println("<p>Erreur base de données </p>");
			out.println(e.getMessage());
		}
	}
}

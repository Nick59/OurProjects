import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;


/**
	Ce fichier redirige juste l'enseignant ou le secr�taire vers la fiche de d�tail de l'�tudiant choisi
*/
public class VersFicheEtu extends HttpServlet{

	public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		/* En-t�te */
		out.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" ><head>       <title>Chargement de la fiche etudiant</title>       <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />	   <link rel=\"stylesheet\" media=\"screen\" type=\"text/css\" title=\"Design\" href=\"../styles/design.css\" />   </head>   <body>");
		/* Fin de l'en-t�te */
		out.println("<h1> Chargement de la fiche en cours... </h1>");
		String url="jdbc:odbc:absences";
		String nom="";
		String mdp="";
		String logine=(String)session.getAttribute("login");
		if(session.getAttribute("login")==null || session.getAttribute("login").equals("")){
			res.sendRedirect("../index.html");
		}
		/* Connexion � la BDD */
		try{
			session.putValue("nomEtu",req.getParameter("nomEtu"));
			res.sendRedirect("FicheEtu");
		}
		catch(Exception e){
			out.println("Erreur co' BDD"+e.getMessage());
		}
	}
}

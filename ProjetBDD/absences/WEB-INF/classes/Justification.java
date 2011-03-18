import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;


public class Justification extends HttpServlet{

	public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		/* En-tête */
		out.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" ><head>       <title>Justification</title>       <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />	   <link rel=\"stylesheet\" media=\"screen\" type=\"text/css\" title=\"Design\" href=\"../styles/design.css\" />   </head>   <body>");
		/* Fin de l'en-tête */
		out.println("<h1> Saisir un justificatif </h1>");
		String url="jdbc:odbc:absences";
		String nom="";
		String mdp="";
		String logine=(String)session.getAttribute("login");
		int role=(Integer)session.getAttribute("statut");
		if(logine==null || logine.equals("") || role!=1){
			res.sendRedirect("../index.html");
		}
		
		out.println("<form method=\"post\" action=\"JustiPost\">");
		out.println("<p><label> Etudiant : </label><input type=\"text\" name=\"login\" /></p>");
		out.println("<p><label> Justification : </label><input type=\"text\" name=\"justificatif\" /></p>");
		out.println("<p><label> Date début : (AAAA/MM/JJ)</label><input type=\"text\" name=\"d1\" /></p>");
		out.println("<p><label> Date fin : (AAAA/MM/JJ)</label><input type=\"text\" name=\"d2\" /></p>");
		out.println("<p><input type=\"submit\" value=\"Justifier l'absence de ce petit polisson hé oui de mon temps on ne faisait pas ca on respectait les professeurs l'ecole c'était toute ma vie je faisais des équations differentielles à 4 ans et demi moi madame !\"/>");
		out.println("</form>");
		
		
		
		/* Connexion à la BDD */
		try{

		}
		catch(Exception e){
			out.println("Erreur co' BDD"+e.getMessage());
		}
	}
}

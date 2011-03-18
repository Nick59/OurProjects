import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;


/**
	Ce fichier deconnecte l'utilisateur et le renvoie a l'index.
*/
public class LogOut extends HttpServlet{

	public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
		PrintWriter out = res.getWriter();
		res.setContentType("text/html");
		HttpSession session=req.getSession(true);
		session.invalidate();
		res.sendRedirect("../index.html");
	}
}

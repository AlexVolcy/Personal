package servlet;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class Validation
 */
@WebServlet("/Validation")
public class Validation extends HttpServlet {
	private static final long serialVersionUID = 1L;
    protected void doGet(HttpServletRequest request, HttpServletResponse response){
    	String eventTitle = request.getParameter("eventTitle");
    	String startDate = request.getParameter("startDate");
    	String endDate = request.getParameter("endDate");
    	String startTime = request.getParameter("startTime");
    	String endTime = request.getParameter("endTime");
    	String next = "/Home.jsp";
    	
    	
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		
    	try {
    		dispatch.forward(request,response);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ServletException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	
    }
}
//    	String email = request.getParameter("email");
//    	String month = request.getParameter("favmonth");
//    	String url = request.getParameter("favweb");
//    	String search = request.getParameter("favsearch");
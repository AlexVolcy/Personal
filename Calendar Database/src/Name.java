
public class Name 
{
	String Fname;
	String Lname;
	
	public Name (String fn, String ln)
	{
		this.Fname = fn;
		this.Lname = ln;
	}
	
	public String getFname() 
	{
		return Fname;
	}

	public void setFname(String fname) 
	{
		Fname = fname;
	}

	public String getLname() 
	{
		return Lname;
	}

	public void setLname(String lname) 
	{
		Lname = lname;
	}
}

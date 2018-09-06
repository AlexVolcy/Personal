
public class Date 
{
	String Month; //December
	int Day; //17
	int Year; //1996
	
	public Date (String Month, int Day, int Year)
	{
		this.Month = Month;
		this.Day = Day;
		this.Year = Year;
	}
	
	public String getMonth() 
	{
		return Month;
	}
	public void setMonth(String month) 
	{
		Month = month;
	}
	public int getDay() 
	{
		return Day;
	}
	public void setDay(int day) 
	{
		Day = day;
	}
	public int getYear() 
	{
		return Year;
	}
	public void setYear(int year) 
	{
		Year = year;
	}
}

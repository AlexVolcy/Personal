
public class Event
{
	String Title;
	String Time; //10:00 am
	Date Date;
	
	public Event(String Title, String Time, Date newDate)
	{
		this.Title = Title;
		this.Time = Time;
		this.Date = newDate;
	}
	
	public String getTitle() 
	{
		return Title;
	}
	public void setTitle(String title) 
	{
		Title = title;
	}
	public String getTime() 
	{
		return Time;
	}
	public void setTime(String time) 
	{
		Time = time;
	}
	public Date getDate() 
	{
		return Date;
	}
	public void setDate(Date date) 
	{
		Date = date;
	}
}

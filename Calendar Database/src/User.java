import java.util.ArrayList;

public class User implements Comparable<User>
{
	Name Name;
	ArrayList<Event> Events;
	
	public User(Name newName, ArrayList<Event> newEvents)
	{
		this.Name = newName; 
		this.Events = newEvents;
	}
	
	public Name getName() 
	{
		return Name;
	}
	public void setName(Name name) 
	{
		Name = name;
	}
	public ArrayList<Event> getEvents() 
	{
		return Events;
	}
	public void setEvents(ArrayList<Event> events) 
	{
		Events = events;
	}

	@Override
	public int compareTo(User o) 
	{
		//string already have a compare to method
		//string.compareTo
		if (this.getName().getLname().compareTo(o.getName().getLname()) == -1)
		{
			return -1;
		}
		else if (this.getName().getLname().compareTo(o.getName().getLname()) == 1)
		{
			return 1;
		}
		else
		{
			if (this.getName().getLname().compareTo(o.getName().getFname()) == -1)
			{
				return -1;
			}
			else if (this.getName().getLname().compareTo(o.getName().getFname()) == 1)
			{
				return 1;
			}
			else
			{
				return 0; 
			}
		}
	}
}

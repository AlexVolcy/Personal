import java.util.Comparator;

public class EventSort implements Comparator<Event>
{
	public int monthConv(String nameOfMonth)
	{
		String lowerMonth = nameOfMonth.toLowerCase();
		
		if (lowerMonth.equals("december")) return 12;
		else if (lowerMonth.equals("november")) return 11;
		else if (lowerMonth.equals("october")) return 10;
		else if (lowerMonth.equals("september")) return 9;
		else if (lowerMonth.equals("august")) return 8;
		else if (lowerMonth.equals("july")) return 7;
		else if (lowerMonth.equals("june")) return 6;
		else if (lowerMonth.equals("may")) return 5;
		else if (lowerMonth.equals("april")) return 4;
		else if (lowerMonth.equals("march")) return 3;
		else if (lowerMonth.equals("february")) return 2;
		else if (lowerMonth.equals("january")) return 1;
		else return 0;
	}
	
	public int compare(Event event1, Event event2) 
	{
		if (event1.getDate().getYear() < event2.getDate().getYear()) return -1;
		else if (event1.getDate().getYear() > event2.getDate().getYear()) return 1;
		else
		{
			if (monthConv(event1.getDate().getMonth()) < monthConv(event2.getDate().getMonth())) return -1; //This 12 > 5
			else if (monthConv(event1.getDate().getMonth()) > monthConv(event2.getDate().getMonth())) return 1; //This 12 < 5
			else
			{
				if (event1.getDate().getDay() < event2.getDate().getDay()) return -1;
				else if (event1.getDate().getDay() > event2.getDate().getDay()) return 1; 
				else return 0; 
			}
		}
	}
}
import java.util.Comparator;

public class UserSortAscending implements Comparator<User>
{
	public int compare(User user1, User user2) 
	{
		//string already have a compare to method
		//string.compareTo
		if (user1.getName().getLname().compareTo(user2.getName().getLname()) < 0)
		{
			return -1;
		}
		else if (user1.getName().getLname().compareTo(user2.getName().getLname()) > 0)
		{
			return 1;
		}
		else
		{
			if (user1.getName().getLname().compareTo(user2.getName().getFname()) < 0)
			{
				return -1;
			}
			else if (user1.getName().getLname().compareTo(user2.getName().getFname()) > 0)
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

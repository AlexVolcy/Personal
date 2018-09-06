//Alexander Volcy
//7797921895

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;
import com.google.gson.Gson;
import com.google.gson.JsonParseException;

public class CalendarDatabase 
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		RootObject rootObject = null; 
		Gson gson = new Gson();
		String jsonFilename;

		
		while (true)
		{
			System.out.print("Enter the input filename: "); //out means we wont have a new line character
			jsonFilename = scan.nextLine();
							
			//Parsing information
			BufferedReader br = null;
			
			try
			{
				br = new BufferedReader(new FileReader(jsonFilename));
				rootObject = gson.fromJson(br, RootObject.class);
				break;
			}
			catch(FileNotFoundException fnfe) {
				System.out.println("That file could not be found.");
				continue;
			}
			catch (JsonParseException jpe)
			{
				System.out.println("That file is not a well-formed JSON file.");
				continue;
			}
		}
		
		
		//Keep track of state of program for save overwrite
		int numOfUsers = rootObject.getUsers().size();
		int numOfEvents = 0;
		for (int i = 0; i < rootObject.getUsers().size(); i++)
		{
			numOfEvents += rootObject.getUsers().get(i).getEvents().size(); 
		}
		boolean hasUserSorted = false; 
		
		//MAIN MENU ::: MAIN MENU ::: MAIN MENU
		//MAIN MENU ::: MAIN MENU ::: MAIN MENU
		int menuChoice = 0; 
		while (menuChoice != 8)
		{
			System.out.println("1) Display User’s Calendar");
			System.out.println("2) Add User");
			System.out.println("3) Remove User");
			System.out.println("4) Add Event");
			System.out.println("5) Delete Event");
			System.out.println("6) Sort Users");
			System.out.println("7) Write File");
			System.out.println("8) Exit");
			System.out.println();
			
			
			//INITIAL USER INPUT 
			System.out.println("What would you like to do? ");

			String stringChoice; 
			stringChoice = scan.nextLine();
			menuChoice = Integer.parseInt(stringChoice);
			
			//SORT EVENTS INITIALLY
			for (int i = 0; i < rootObject.getUsers().size(); i++)
			{
				//Sorted Events? 
				Collections.sort(rootObject.getUsers().get(i).getEvents(), new EventSort());
			}
			
						
			//INVALID OPTION
			if (menuChoice > 8 || menuChoice < 0)
			{
				System.out.println("That is not a valid option");
				continue;
			}
			//DISPLAY CALENDAR
			else if (menuChoice == 1)
			{
				for (int i = 0; i < rootObject.getUsers().size(); i++)
				{
					//Trojan, Tommy
					System.out.print(rootObject.getUsers().get(i).getName().getLname());
					System.out.print(", "); 
					System.out.println(rootObject.getUsers().get(i).getName().getFname());
					
					
					for (int j = 0; j < rootObject.getUsers().get(i).getEvents().size(); j++)
					{
						char letterBullet = (char) (j+97); 
						String printTitle = rootObject.getUsers().get(i).getEvents().get(j).getTitle();
						String printTime = rootObject.getUsers().get(i).getEvents().get(j).getTime();
						String printMonth = rootObject.getUsers().get(i).getEvents().get(j).getDate().getMonth();
						int printDay = rootObject.getUsers().get(i).getEvents().get(j).getDate().getDay();
						int printYear = rootObject.getUsers().get(i).getEvents().get(j).getDate().getYear();
						System.out.println("\t" + letterBullet + ". " + printTitle + ", " + printTime + ", " + printMonth + " " + printDay + ", " + printYear);
					}		
					//use an interface, comparable interface compareTo, returns -1, 0, 1
				}
			}
			//ADD USER
			else if (menuChoice == 2)
			{	
				String fName;
				String lName = "";
				System.out.print("What's the user's name? ");
				
				String fullName = scan.nextLine(); //Alex Volcy
				String[] splitName = fullName.split(" ", 2); //Alex
				fName = splitName[0];
				lName = splitName[1];
				
				//Checking to see if user already exists
				for (int i = 0; i < rootObject.getUsers().size(); i++)
				{
					String lowerLName1 = splitName[1].toLowerCase();
					String lowerLName2 = rootObject.getUsers().get(i).getName().getLname().toLowerCase();
					String lowerFName1 = splitName[0].toLowerCase();
					String lowerFName2 = rootObject.getUsers().get(i).getName().getFname().toLowerCase();
					if (lowerLName1.equals(lowerLName2) && lowerFName1.equals(lowerFName2))
					{
						System.out.println("User already exists");
						System.out.println("");
						continue;
					}
				}
				Name newUserName = new Name(fName, lName);
				ArrayList<Event> newUserEvents = new ArrayList<Event>();
				
				User newUser = new User(newUserName, newUserEvents);
				
				rootObject.getUsers().add(newUser);
			}
			//REMOVE USER (and their appointments) 
			else if (menuChoice == 3)
			{
				System.out.print("What's the user's first name? ");
				String fNameRemove = scan.nextLine();
				
				System.out.print("What's the user's last name? ");
				String lNameRemove = scan.nextLine();
				
				fNameRemove = fNameRemove.toLowerCase();
				lNameRemove = lNameRemove.toLowerCase();
				
				for (int i = 0; i < rootObject.getUsers().size(); i++)
				{
					if (rootObject.getUsers().get(i).getName().getFname().toLowerCase().equals(fNameRemove))
					{
						if (rootObject.getUsers().get(i).getName().getLname().toLowerCase().equals(lNameRemove))
						{
							rootObject.getUsers().remove(i);
						}
					}
				}
			}
			//ADD EVENT
			else if (menuChoice == 4)
			{
				for (int i = 0; i < rootObject.getUsers().size(); i++)
				{
					//Trojan, Tommy
					System.out.print((i+1) + ") ");
					System.out.print(rootObject.getUsers().get(i).getName().getLname());
					System.out.print(", "); 
					System.out.println(rootObject.getUsers().get(i).getName().getFname());
				}
				
				System.out.print("To which user would you like to add an event?");
				int userChoice = 0;
				String userStringChoice = scan.nextLine();
				userChoice = Integer.parseInt(userStringChoice);
				
				System.out.print("What is the title of the event? ");
				String newTitle = scan.nextLine();
				
				System.out.print("What time is the event? ");
				String newTime = scan.nextLine();
				
				int newNumMonth = 0; 
				String newMonth = "";
				while (true)
				{
					System.out.print("What month? ");
					newMonth = scan.nextLine();
					newNumMonth = Integer.parseInt(newMonth);
					if (newNumMonth > 12 || newNumMonth < 1)
					{
						System.out.println("Enter a valid month");
						continue;
					}
					break;
				}
				newMonth = monthConv(newNumMonth);
				
				
				int newDay = 0; 
				String newStringDay = "";
				while (true)
				{
					System.out.print("What day? ");
					newStringDay = scan.nextLine();
					newDay = Integer.parseInt(newStringDay);
					if (newDay > 31 || newDay < 1)
					{
						System.out.println("Enter a valid day");
						continue;
					}
					break;
				}

				System.out.print("What year? ");
				int newYear = 0;
				String newStringYear = scan.nextLine();
				newYear = Integer.parseInt(newStringYear);
				
				Date newDate = new Date(newMonth, newDay, newYear);
				Event newEvent = new Event(newTitle, newTime, newDate);
				
				rootObject.getUsers().get(userChoice-1).getEvents().add(newEvent);
				
				System.out.print("Added: " + newTitle + ", " + newTime + ", " + newMonth + " " + newDay + ", " + newYear +  " to ");
				System.out.print(rootObject.getUsers().get(userChoice-1).getName().getFname() + " ");
				System.out.println(rootObject.getUsers().get(userChoice-1).getName().getLname() + "'s calendar.");
				
				for (int i = 0; i < rootObject.getUsers().size(); i++)
				{
					//Sorted Events? 
					Collections.sort(rootObject.getUsers().get(i).getEvents(), new EventSort());
				}
				
			}
			//DELETE EVENT
			else if (menuChoice == 5)
			{
				//Print users names
				for (int i = 0; i < rootObject.getUsers().size(); i++)
				{
					//Trojan, Tommy
					System.out.print((i+1) + ") ");
					System.out.print(rootObject.getUsers().get(i).getName().getLname());
					System.out.print(", "); 
					System.out.println(rootObject.getUsers().get(i).getName().getFname());
				}
				
				System.out.print("From which user would you like to delete an event? ");
				int userChoice = 0;
				String userStringChoice = scan.nextLine();
				userChoice = Integer.parseInt(userStringChoice);
				
				if (rootObject.getUsers().get(userChoice-1).getEvents().size() == 0) 
				{
					System.out.println("Calendar is empty.");
					System.out.println("");
					continue;
				}
				
				String printTitle = "";
				for (int j = 0; j < rootObject.getUsers().get(userChoice-1).getEvents().size(); j++)
				{
					printTitle = rootObject.getUsers().get(userChoice-1).getEvents().get(j).getTitle();
					String printTime = rootObject.getUsers().get(userChoice-1).getEvents().get(j).getTime();
					String printMonth = rootObject.getUsers().get(userChoice-1).getEvents().get(j).getDate().getMonth();
					int printDay = rootObject.getUsers().get(userChoice-1).getEvents().get(j).getDate().getDay();
					int printYear = rootObject.getUsers().get(userChoice-1).getEvents().get(j).getDate().getYear();
					
					System.out.println("\t" + (j+1) + ") " + printTitle + ", " + printTime + ", " + printMonth + " " + printDay + ", " + printYear);
				}
				
				int eventDeleteChoice = 0;
				String userEventChoice = scan.nextLine();
				eventDeleteChoice = Integer.parseInt(userEventChoice);
				
				printTitle = rootObject.getUsers().get(userChoice-1).getEvents().get(eventDeleteChoice-1).getTitle();
				rootObject.getUsers().get(userChoice-1).getEvents().remove(eventDeleteChoice-1);
				System.out.println(printTitle + " has been deleted");
				System.out.println("");
			}
			//SORT USERS
			else if (menuChoice == 6)
			{
				System.out.println("1) Ascending (A-Z) ");
				System.out.println("2) Descending (Z-A) ");
				System.out.println("How would you like to sort? ");
				
				int userChoice = 0;
				String userStringChoice = scan.nextLine();
				userChoice = Integer.parseInt(userStringChoice);
				
				if (userChoice == 1)
				{
					Collections.sort(rootObject.getUsers(), new UserSortAscending());
					for (int i = 0; i < rootObject.getUsers().size(); i++)
					{
						//Trojan, Tommy
						System.out.print((i+1) + ") ");
						System.out.print(rootObject.getUsers().get(i).getName().getLname());
						System.out.print(", "); 
						System.out.println(rootObject.getUsers().get(i).getName().getFname());
					}
					hasUserSorted = true;
				}
				else if (userChoice == 2)
				{
					Collections.sort(rootObject.getUsers(), new UserSortDescending());
					for (int i = 0; i < rootObject.getUsers().size(); i++)
					{
						//Trojan, Tommy
						System.out.print((i+1) + ") ");
						System.out.print(rootObject.getUsers().get(i).getName().getLname());
						System.out.print(", "); 
						System.out.println(rootObject.getUsers().get(i).getName().getFname());
					}
					hasUserSorted = true;
				}

			}
			//WRITE FILE
			else if (menuChoice == 7) 
			{
				try {
					FileWriter writer = new FileWriter(jsonFilename);
					String jsonString = gson.toJson(rootObject);
					writer.write(jsonString);
					writer.close();
					
					//Update numbers
					numOfUsers = rootObject.getUsers().size();
					for (int i = 0; i < rootObject.getUsers().size(); i++)
					{
						numOfEvents += rootObject.getUsers().get(i).getEvents().size(); 
					}
					System.out.println("File was saved.");
				} catch (IOException e) 
				{
					e.printStackTrace();
				}
			}
			//EXIT
			else if (menuChoice == 8)
			{
				//if users are now sorted
				
				//Update sizes
				int changeUserSizeCheck = rootObject.getUsers().size();
				int changeEventsSizeCheck = 0;
				for (int i = 0; i < rootObject.getUsers().size(); i++)
				{
					changeEventsSizeCheck += rootObject.getUsers().get(i).getEvents().size(); 
				}
				
				if (changeUserSizeCheck != numOfUsers || changeEventsSizeCheck != numOfEvents || hasUserSorted)
				{
					printChangesPrompt();
					
					int userChoice = 0;
					String userStringChoice = scan.nextLine();
					userChoice = Integer.parseInt(userStringChoice); 
					
					if (userChoice == 1)
					{
						try {
							FileWriter writer = new FileWriter(jsonFilename);
							String jsonString = gson.toJson(rootObject);
							writer.write(jsonString);
							writer.close();
							
							//Update numbers
							numOfUsers = rootObject.getUsers().size();
							for (int i = 0; i < rootObject.getUsers().size(); i++)
							{
								numOfEvents += rootObject.getUsers().get(i).getEvents().size(); 
							}
							System.out.println("File was saved.");
							System.out.println();
							hasUserSorted = false;
						} catch (IOException e) 
						{
							e.printStackTrace();
						}
					}
					else
					{
						System.out.println("File was not saved.");
					}
				}
				System.out.println("Thanks for using Alé's program!");
			}
		}
	}
	public static void printChangesPrompt()
	{
		System.out.println("Changes have been made since the file was last saved.");
		System.out.println("1) Yes");
		System.out.println("2) No");
		System.out.println("Would you like to save the file before exiting?");
	}
	public static String monthConv(int numOfMonth)
	{	
		if (numOfMonth == 12) return "December";
		else if (numOfMonth == 11) return "November";
		else if (numOfMonth == 10) return "October";
		else if (numOfMonth == 9) return "September";
		else if (numOfMonth == 8) return "August";
		else if (numOfMonth == 7) return "July";
		else if (numOfMonth == 6) return "June";
		else if (numOfMonth == 5) return "May";
		else if (numOfMonth == 4) return "April";
		else if (numOfMonth == 3) return "March";
		else if (numOfMonth == 2) return "February";
		else return "January";
	}
}

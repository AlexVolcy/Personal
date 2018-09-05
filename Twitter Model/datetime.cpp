#include "datetime.h"

using namespace std;

DateTime::DateTime()
{
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	hour = timeinfo->tm_hour;
	min = timeinfo->tm_min;
	sec = timeinfo->tm_sec; 
	year = timeinfo->tm_year + 1900;
	month = 1 + timeinfo->tm_mon;
	day = timeinfo->tm_mday;
}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
	hour = hh;
	min = mm;
	sec = ss;
	this->year = year;
	this->month = month;
	this->day = day; 
}

bool DateTime::operator<(const DateTime& other) const
{
	if (year < other.year)
	{
		return true;
	}
	else if (year == other.year)
	{
		if (month < other.month)
		{
			return true;
		}
		else if (month == other.month)
		{
			if (day < other.day)
			{
				return true;
			}
			else if (day == other.day)
			{
				if(hour < other.hour)
				{
					return true;
				}	
				else if (hour == other.hour)
				{
					if (min < other.min)
					{
						return true; 
					}
					else if (min == other.min)
					{
						if (sec < other.sec || sec == other.sec)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false; //if any of these go the opposite way, then we'll retunrn false; 	
}

ostream& operator<<(ostream& os, const DateTime& other)
{
	os << setfill('0') << setw(4) << other.year << "-";
	os << setfill('0') << setw(2) << other.month << "-";
	os << setfill('0') << setw(2) << other.day << " ";
	os << setfill('0') << setw(2) << other.hour << ":";
	os << setfill('0') << setw(2) << other.min << ":";
	os << setfill('0') << setw(2) << other.sec;
	return os;
}

istream& operator>>(istream& is, DateTime& dt)
{
	DateTime currTime;
	string yearCheck;
	string monthCheck;
	string dayCheck;
	string hourCheck;
	string minCheck;
	string secCheck; 

	//2018-
	getline(is, yearCheck, '-');
	stringstream ss(yearCheck);
	if (ss.fail()){
		dt = currTime;
		return is;
	}
	else{
		ss >> dt.year;
	}
	//05-
	getline(is, monthCheck, '-');
	stringstream as(monthCheck);
	if (as.fail()){
		dt = currTime;
		return is;
	}
	else{
		as >> dt.month;
	}
	//20-
	getline(is, dayCheck, ' ');
	stringstream bs(dayCheck);
	if (bs.fail()){
		dt = currTime;
		return is;
	}
	else{
		bs >> dt.day;
	}
	//12:
	getline(is, hourCheck, ':');
	stringstream cs(hourCheck);
	if (cs.fail()){
		dt = currTime;
		return is;
	}
	else{
		cs >> dt.hour;
	}
	//:35:
	getline(is, minCheck, ':');
	stringstream ds(minCheck);
	if (ds.fail()){
		dt = currTime;
		return is;
	}
	else{
		ds >> dt.min;
	}
	//:14
	getline(is, secCheck, ' ');
	stringstream es(secCheck);
	if (es.fail()){
		dt = currTime;
		return is;
	}
	else{
		es >> dt.sec;
	}


	return is;
}


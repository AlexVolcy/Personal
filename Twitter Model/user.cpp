#include "user.h"
#include "msort.h"
#include <ctype.h>

using namespace std;


User::User(string name)
{
	userName = name;
}

User::~User()
{
	//clean up handled in twiteng
}

string User::name() const
{
	return this->userName;
}

set<User*> User::followers() const
{
	return this->followers_; 
}

set<User*> User::following() const
{
	return this->following_;
}

list<Tweet*> User::tweets() const
{
	return this->tweets_;
}

void User::addFollower(User* u)
{
	followers_.insert(u);
}

void User::addFollowing(User* u)
{
	following_.insert(u);
}

void User::addTweet(Tweet* t)
{
	tweets_.push_back(t);
}

void User::setID(const int userID)
{
	this->id = userID;
}

void User::setLLV(const int llvID)
{
	this->llv = llvID; 
}

int User::getID()
{
	return this->id; 
}

int User::getLLV()
{
	return this->llv; 
}

vector<Tweet*> User::getFeed()
{
	vector<Tweet*> feed;
	for (set<User*>::iterator it = following_.begin(); it != following_.end(); ++it)//find each person i follow
	{
		list<Tweet*> temp = (*it)->tweets();
		for (list<Tweet*>::iterator jt = temp.begin(); jt != temp.end(); ++jt)
		{
			string textOfTweet = (*jt)->text();
			if (textOfTweet[0] == '@')
			{
				stringstream ss(textOfTweet);
				string username_;
				ss >> username_;
				username_ = username_.substr(1, string::npos);

				if (username_ == name()) //if its the first thing, that tweet should be added to their feed but no on elses
				{
					//i follow them but they also need to follow me too
					set<User*> specialMention = (*it)->following();
					set<User*>::iterator xt;
					xt = specialMention.find(this);
					if (xt != specialMention.end())
					{
						feed.push_back(*jt);
					}
				} 
			}
			else
			{
				feed.push_back(*jt);
			}
		}
	}
	for (list<Tweet*>::iterator it = tweets_.begin(); it != tweets_.end(); ++it)//iterate over my list of tweets and push back each tweet
	{
		feed.push_back(*it);
	}
	TweetComp comp1;
	mergeSort(feed, comp1);
	return feed; 
}







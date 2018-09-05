#include "tweet.h"
#include "user.h"


using namespace std;


Tweet::Tweet()
{
	//default
}

Tweet::Tweet(User* user, const DateTime& time, const string& text)
{
	user_ = user;
	timeStamp = time; 
	textOfTweet = text; 
}

DateTime const & Tweet::time() const
{
	return this->timeStamp;
}

string const & Tweet::text() const
{
	return this->textOfTweet;
}

set<string> Tweet::hashTags() const
{
	//loop through text of tweet and if char == #, push the word that follows into our hashtags set
	stringstream ss(textOfTweet);
	string parseHashtag;
	set<string> hashtagsInTweet;

	while (ss >> parseHashtag)
	{
		if (parseHashtag[0] == '#')
		{
			string noHashtag;
			noHashtag = parseHashtag.substr(1, string::npos);
			hashtagsInTweet.insert(noHashtag);
		}
	}
	return hashtagsInTweet;
}

bool Tweet::operator<(const Tweet& other) const
{
	if (this->timeStamp < other.timeStamp)
	{
		return true;
	}
	return false; 
}

ostream& operator<<(ostream& os, const Tweet& t)
{
	os << t.timeStamp << " " << t.user_->name() << " " << t.text();
	return os; 
}





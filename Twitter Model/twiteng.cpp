#include "twiteng.h"
#include "util.h"
#include "msort.h"
#include <ctype.h>

using namespace std;

TwitEng::TwitEng() : trending_(2)
{
	currUser = "NULL";
}

TwitEng::~TwitEng()
{
	map<string, User*>::iterator it; 

	for (it = allUsers.begin(); it != allUsers.end(); ++it)
	{
		list<Tweet*> temp = it->second->tweets(); 
		list<Tweet*>::iterator jt;
		for (jt = temp.begin(); jt != temp.end(); ++jt)
		{
			delete *jt;
		}
		delete it->second;
	}
}

//Parses the Twitter database and populates internal structures
bool TwitEng::parse(char* filename)
{
	ifstream ifile(filename);

	int numOfUsers;
	ifile >> numOfUsers; //defines the amount of times our loop will run 
	string buf;
	getline(ifile, buf);

	string users;
	string mainUser;
	string parseUsers;
	int hashPassword;

	for (int i = 0; i < numOfUsers; i++)
	{
		getline(ifile, users);//get line of users
		stringstream ss(users);
		ss >> mainUser;//this is the main user, with the preceding users being the ones he follows 

		//**CREATES A NEW USER W/ PASSWORD***
		if (!(allUsers.find(mainUser) != allUsers.end())) //user is unique
		{
			User* myUser = new User(mainUser); //create new user
			allUsers.insert(make_pair(mainUser, myUser));

			ss >> hashPassword;
			allPasswords.insert(make_pair(myUser, hashPassword));
		}
		else //user is not unique, but we do need to add to its passwords map
		{
			ss >> hashPassword;
			map<string, User*>::iterator bt = allUsers.find(mainUser);
			User* temp = bt->second;
			allPasswords.insert(make_pair(temp, hashPassword));
		}
		//**FOR THE NEW USER CREATED, ADD TO THEIR LIST OF FOLLOWINGS

		while (ss >> parseUsers) //add to the list of followings 
		{
			if (!(allUsers.find(parseUsers) != allUsers.end()))//if the person i want to follow isn't a user already
			{
				User* userIFollow = new User(parseUsers);//create the user that I follow
				allUsers.insert(make_pair(parseUsers, userIFollow));

				map<string, User*>::iterator it = allUsers.find(mainUser);//find the main user so that we can append addfollowing 
				if (it != allUsers.end()){
					it->second->addFollowing(userIFollow);//add following
				}
			}
			else //user i want to follow is already a user
			{
				map<string, User*>::iterator it = allUsers.find(mainUser); //find my the user that will have its followings appended
				if (it != allUsers.end()){
					map<string, User*>::iterator jt = allUsers.find(parseUsers);//find the user that i want to add in
					if (jt != allUsers.end()){
						it->second->addFollowing(jt->second);
					}
				}
			}
		}
	}

	while(!ifile.fail())//loop to get the tweets
	{
		string tweetAndTimeStamp;
		string buf;
		string username;
		DateTime dt;

		getline(ifile, tweetAndTimeStamp); //whole tweet is now captured by tweetAndTimeStamp

		//parse time and username 
		stringstream ss(tweetAndTimeStamp);
		ss >> dt; 
		ss >> username; //we look at who tweeted the tweet, and add that tweet to the User's user object
		getline(ss, buf, ' ');
		getline(ss, tweetAndTimeStamp);

		if(!ss.fail()) addTweet(username, dt, tweetAndTimeStamp); 
	}
	return false;
}

//Allocates a tweet from its parts and adds it to internal structures
void TwitEng::addTweet(const string& username, const DateTime& time, const string& text)
{
	map<string, User*>::iterator it = allUsers.find(username);
	if (it != allUsers.end())//adds the tweet
	{
		Tweet* newTweet = new Tweet(it->second, time, text);
		addHashtags(text, newTweet);
		addMentions(text, newTweet);
		it->second->addTweet(newTweet);
	}
}

void TwitEng::addHashtags(string textOfTweet, Tweet* newTweet)
{
	stringstream ss(textOfTweet);
	string parseTweet;
	string newHashtag;

	while (ss >> parseTweet)
	{
		if (parseTweet[0] == '#'){
			convLower(parseTweet);
			newHashtag = parseTweet.substr(1, string::npos);
			map<string, set<Tweet*> >::iterator it = allHashtags.find(newHashtag);
			if (it != allHashtags.end())
			{
				it->second.insert(newTweet);
				//****update key****
				TagData old(it->first, it->second.size()-1);
				TagData newVal(it->first, it->second.size());
				trending_.decreaseKey(old, newVal);
			}
			else
			{ //if the hashtag is unique
				set<Tweet*> newTweetSet; 
				newTweetSet.insert(newTweet);
				allHashtags.insert(make_pair(newHashtag, newTweetSet));

				//****new addition****
				TagData newHashtagTrend(newHashtag, 1);
				trending_.push(newHashtagTrend);
			}
		}
	}
}

void TwitEng::addMentions(string textOfTweet, Tweet* newTweet)
{
	stringstream ss(textOfTweet);
	string parseTweet;
	int count = 0;
	bool found = false; 
	while (ss >> parseTweet)
	{
		if (parseTweet[0] == '@' && count == 0) //handles the special case where the @ symbol comes first 
		{
			parseTweet = parseTweet.substr(1, string::npos);
			map<string, set<Tweet*> >::iterator it = allMentions.find(parseTweet);
			if (it != allMentions.end() && it->first == parseTweet){
				it->second.insert(newTweet);
				found = true; 
			}
			if (!found){ //if we couldn't find that mention before we need to make a new set of it
				set<Tweet*> newTweetSet;
				newTweetSet.insert(newTweet);
				allMentions.insert(make_pair(parseTweet, newTweetSet));
			}
			break;
		}
		else if (parseTweet[0] == '@'){ 
			parseTweet = parseTweet.substr(1, string::npos);
			map<string, set<Tweet*> >::iterator it = allMentions.find(parseTweet);
			if (it != allMentions.end() && it->first == parseTweet){
				it->second.insert(newTweet);
				found = true; 
			}
			if (!found){ //if we couldn't find that mention before we need to make a new set of it
				set<Tweet*> newTweetSet;
				newTweetSet.insert(newTweet);
				allMentions.insert(make_pair(parseTweet, newTweetSet));
			}
		}
		count++;
	}
}

void TwitEng::addAFollowing(string myUsername, string userIFollow)
{
	map<string, User*>::iterator it = allUsers.find(myUsername);
	if (it != allUsers.end())
	{
		map<string, User*>::iterator jt = allUsers.find(userIFollow);
		if (jt != allUsers.end())
		{
			it->second->addFollowing(jt->second);
		}
	}
}

void TwitEng::databaseDump(string filename)
{
	ofstream datFile(filename.c_str());
	
	//print out all of the users + follow relationships
	map<string, User*>::iterator it;
	for (it = allUsers.begin(); it != allUsers.end(); ++it)
	{
		//Mark
		datFile << it->first << " ";

		//28114
		map<User*, unsigned int>::iterator xt = allPasswords.find(it->second);
		datFile << xt->second << " ";

		//Tommy Jill
		set<User*> temp = it->second->following();
		set<User*>::iterator jt;
		for (jt = temp.begin(); jt != temp.end(); ++jt)
		{
			datFile << (*jt)->name() << " ";
		}
		datFile << endl;
	}
	//print out all the tweets
	for (it = allUsers.begin(); it != allUsers.end(); ++it)
	{
		list<Tweet*> temp = it->second->tweets();
		list<Tweet*>::iterator jt;
		for (jt = temp.begin(); jt != temp.end(); ++jt)
		{
			datFile << **jt << endl;
		}
	}
}

void setUnion(set<Tweet*>& firstSet, const set<Tweet*>& secondSet)
{
	set<Tweet*>::iterator jt;
	for (jt = secondSet.begin(); jt != secondSet.end(); ++jt)
	{
		firstSet.insert(*jt);
	}
}

set<Tweet*> setIntersection(const set<Tweet*>& firstSet, const set<Tweet*>& secondSet)
{
	set<Tweet*> interSet;
	set<Tweet*>::iterator it;
	set<Tweet*>::iterator jt;
	jt = secondSet.begin();

	for (it = firstSet.begin(); it != firstSet.end(); ++it)
	{
		if (secondSet.find(*it) != secondSet.end()){
			interSet.insert(*it);
		}
	}
	return interSet; 
}

vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy)
{
	//create a set
	vector<Tweet*> finalHashtags; 
	set<Tweet*> foundHashtags; 
	vector<Tweet*> emptySet;

	if (strategy == 0)//AND
	{
		for (unsigned int i = 0; i < terms.size(); i++)
		{
			convLower(terms[i]);
 			map<string, set<Tweet*> >::iterator it = allHashtags.find(terms[i]);
			if (it != allHashtags.end() && i == 0)
			{
				foundHashtags = it->second;
			}
			else if (allHashtags.find(terms[i]) != allHashtags.end())
			{
				set<Tweet*> itTweets = it->second;
				foundHashtags = setIntersection(foundHashtags, itTweets);
			}
			else
			{
				return emptySet;
			}
		}
		set<Tweet*>::iterator it;
		for (it = foundHashtags.begin(); it != foundHashtags.end(); ++it)
		{
			finalHashtags.push_back(*it);
		}
	}
	else if (strategy == 1)//OR
	{
		for (unsigned int i = 0; i < terms.size(); i++) //will loop over each word that the user wants to look up
		{
			convLower(terms[i]);
			map<string, set<Tweet*> >::iterator it = allHashtags.find(terms[i]);
			if (it != allHashtags.end())//we will find the hashtags in our hashtags map 
			{
				set<Tweet*> itTweets = it->second; //then access the vector of tweets that have that hashtag in it
				setUnion(foundHashtags, itTweets);
			}
		}
		set<Tweet*>::iterator it;
		for (it = foundHashtags.begin(); it != foundHashtags.end(); ++it)
		{
			finalHashtags.push_back(*it);
		}
	}
	return finalHashtags;
}

//Dump feeds of each user to their own file
void TwitEng::dumpFeeds()
{
	//prints out all the users normal feeds
	map<string, User*>::iterator it;
	for (it = allUsers.begin(); it != allUsers.end(); ++it)
	{
		User* itUser = it->second;//helps w/ syntax
		vector<Tweet*> tweetsForFeed = itUser->getFeed(); 

		string filename = it->first + ".feed";
		ofstream out(filename.c_str());

		out << itUser->name() << endl; 
		for (unsigned int i = 0; i < tweetsForFeed.size(); i++)
		{
			out << *tweetsForFeed[i] << endl;
		}
	}

	//prints out all the users mentions' feed
	map<string, set<Tweet*> >::iterator jt;
	for (jt = allMentions.begin(); jt != allMentions.end(); ++jt)
	{

		//set up file names
		string filename = jt->first + ".mentions";
		ofstream ofile(filename.c_str());
		ofile << jt->first << endl;

		//set up mentions that will be sorted 
		set<Tweet*> mentions = jt->second;
		vector<Tweet*> copyMentions;

		set<Tweet*>::iterator xt;
		for (xt = mentions.begin(); xt != mentions.end(); ++xt)
		{
			copyMentions.push_back(*xt);
		}

		//sort mentions feed
		TweetComp comp1;
		mergeSort(copyMentions, comp1);

		//print
		for (unsigned int i = 0; i < copyMentions.size(); i++)
		{
			ofile << *copyMentions[i];
			ofile << endl;
		}
	}
}

void TwitEng::sccDump(string filename)
{
	ofstream ofile(filename.c_str());

	//set every ID to unvisited
	map<string, User*>::iterator it;
	for (it = allUsers.begin(); it != allUsers.end(); ++it)
	{
		it->second->setID(0); //0 means unvisited 
		it->second->setLLV(0); //initial exploration has the ids and LLVs be equal
	}
	int id = 0;
	for (it = allUsers.begin(); it != allUsers.end(); ++it)
	{
		if (it->second->getID() == 0)
		{
			DFS(it->second, id);
			seenSet.clear();
 		}
	}
	for (unsigned int i = 0; i < connComps.size(); i++)
	{
		ofile << "Component " << i+1 << endl;
		set<User*> temp = connComps[i];
		set<User*>::iterator ht;
		for (ht = temp.begin(); ht != temp.end(); ++ht)
		{
			ofile << (*ht)->name() << endl;
		}
		ofile << endl;
	}
}

void TwitEng::DFS(User* mainNode, int& id)
{ 
	//push onto stacks and assign values
	mainStack.push(mainNode);
	seenSet.insert(mainNode);

	++id;
	mainNode->setID(id);
	mainNode->setLLV(id);

	//meet the neighbors 
	set<User*> following = mainNode->following();

	//when exploring a nodes neighbors, you stop once you get back to the main node
	//dive deep to look at all them neighbors fam
	set<User*>::iterator jt;
	for (jt = following.begin(); jt != following.end(); ++jt)
	{
		if ((*jt)->getID() == 0)//if the node is unexplored, recurse 
		{
			DFS((*jt), id); //need to follow it's path now
			mainNode->setLLV(min(mainNode->getLLV(), (*jt)->getLLV()));
		}
		else if ((*jt)->getID() != 0) //if the node we're xploring is on stack and has been visited 
		{
			set<User*>::iterator xt = seenSet.find(*jt);
			if (xt != seenSet.end())
			{
				mainNode->setLLV(min(mainNode->getLLV(), (*jt)->getID()));
			}
		}
	}
	if (mainNode->getID() == mainNode->getLLV()) //foudn root of SCC 
	{
		set<User*> comps;
		User* temp;

		//create a set of the connected components
		//and push onto vector that will be printed later
		do
		{
			temp = mainStack.top();
			comps.insert(temp);
			mainStack.pop();
		} while (temp != mainNode);

		connComps.push_back(comps);
		return;
	}
}

string TwitEng::getCurrUser()
{
	return currUser;
}

void TwitEng::Trending(int n)
{ 
	vector<TagData> temp;
	for (int i = 0; i < n && !trending_.empty(); i++)
	{
		cout << trending_.top().tag << " : ";
		cout << trending_.top().num << endl;

		TagData tempTag(trending_.top().tag, trending_.top().num);
		temp.push_back(tempTag);
		trending_.pop();
	}

	//Need to make sure the heap doesn't get ultimately altered.
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		trending_.push(TagData(temp[i].tag, temp[i].num));
	}
}

bool TwitEng::login(string username, string password)
{
	map<std::string, User*>::iterator jt = allUsers.find(username);
	map<User*, unsigned int>::iterator it = allPasswords.find(jt->second);

	unsigned long long passwordCheck;
	if (it != allPasswords.end())
	{
		passwordCheck = calculateHash(password);
		if (passwordCheck == it->second)
		{
			currUser = username;
			return true; 
		}
	}
	return false;
}

void TwitEng::logout()
{
	currUser = "NULL";
	cout << "Logout successful." << endl;
}
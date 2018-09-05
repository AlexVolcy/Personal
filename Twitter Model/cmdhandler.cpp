#include "cmdhandler.h"
#include "util.h"
#include "datetime.h"
#include <sstream>
#include <iostream>

using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";
}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
	: Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	vector<string> terms;
	vector<Tweet*> tweets;
	string parseTerm; 

	while(instr >> parseTerm) {terms.push_back(parseTerm);}

	tweets = eng->search(terms, 0);
	displayHits(tweets);
	return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
	: Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	vector<string> terms;
	vector<Tweet*> tweets;
	string parseTerm; 

	while(instr >> parseTerm) {terms.push_back(parseTerm);}

	tweets = eng->search(terms, 1);
	displayHits(tweets);
	return HANDLER_OK;
}

TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
	: Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{
	if (eng->getCurrUser() == "NULL")
	{
		cout << "Error, no one logged in" << endl;
		return HANDLER_ERROR;
	}
	//tweet needs username, time, and text
	string username;
	DateTime currTime;
	//instr >> username;

	string buf; 
	string textOfTweet;

	getline(instr, buf, ' ');
	getline(instr, textOfTweet);

	username = eng->getCurrUser();

	eng->addTweet(username, currTime, textOfTweet);
	return HANDLER_OK;
}

FollowHandler::FollowHandler()
{

}

FollowHandler::FollowHandler(Handler* next)
	: Handler(next)
{

}

bool FollowHandler::canHandle(const std::string& cmd) const
{
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng* eng, std::istream& instr) const
{
	if (eng->getCurrUser() == "NULL")
	{
		cout << "Error, no one logged in" << endl;
		return HANDLER_ERROR;
	}
	//note: the instr will give us the name of the user, and the name of the person they want to follow
	string myUsername;
	string following;

	// instr >> myUsername;
	instr >> following;	
	myUsername = eng->getCurrUser();

	eng->addAFollowing(myUsername, following);
	return HANDLER_OK;
}

SaveHandler::SaveHandler()
{

}

SaveHandler::SaveHandler(Handler* next)
	: Handler(next)
{

}

bool SaveHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng* eng, std::istream& instr) const
{
	string filename;
	instr >> filename;
	eng->databaseDump(filename);
	return HANDLER_OK;
}

SCCHandler::SCCHandler()
{

}

SCCHandler::SCCHandler(Handler* next)
	: Handler(next)
{

}

bool SCCHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SCC";
}

Handler::HANDLER_STATUS_T SCCHandler::process(TwitEng* eng, std::istream& instr) const
{
	string filename;
	instr >> filename;
	eng->sccDump(filename);
	return HANDLER_OK;
}

TrendingHandler::TrendingHandler()
{

}

TrendingHandler::TrendingHandler(Handler* next)
	: Handler(next)
{

}

bool TrendingHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TRENDING";
}

Handler::HANDLER_STATUS_T TrendingHandler::process(TwitEng* eng, std::istream& instr) const
{
	int n;
	instr >> n;
	eng->Trending(n);
	return HANDLER_OK;
}

LoginHandler::LoginHandler()
{

}

LoginHandler::LoginHandler(Handler* next)
	: Handler(next)
{

}

bool LoginHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGIN";
}

Handler::HANDLER_STATUS_T LoginHandler::process(TwitEng* eng, std::istream& instr) const
{
	string username;
	string password;
	bool successfulLogin;

	instr >> username;
	instr >> password;

	successfulLogin = eng->login(username, password);
	if (successfulLogin)
	{
		cout << "Login successful." << endl; 
		return HANDLER_OK;
	}
	cout << "Invalid username/password." << endl;
	return HANDLER_ERROR; 
}

LogoutHandler::LogoutHandler()
{

}

LogoutHandler::LogoutHandler(Handler* next)
	: Handler(next)
{

}

bool LogoutHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGOUT";
}

Handler::HANDLER_STATUS_T LogoutHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->logout();
	return HANDLER_OK;
}
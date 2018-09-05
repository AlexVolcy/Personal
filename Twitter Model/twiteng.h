#ifndef TWITENG_H
#define TWITENG_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include <sstream> 
#include <iostream>
#include <fstream>
#include <stack> 
#include <cmath> 
#include "user.h"
#include "datetime.h"
#include "tweet.h"
#include "heap.h"
#include "tagdata.h"
#include "hash.h"

class TwitEng
{
 public:
  TwitEng();
  ~TwitEng();
  /**
   * Parses the Twitter database and populates internal structures
   * @param filename of the database file
   * @return true if there is an error, false if successful
   */
  bool parse(char* filename);

  /**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */
  void addTweet(const std::string& username, const DateTime& time, const std::string& text);

  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
  std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);

  std::string getCurrUser();
  /**
   * Dump feeds of each user to their own file
   */
  void dumpFeeds();

  /* You may add other member functions */
  void addHashtags(std::string, Tweet*);
  void addMentions(std::string, Tweet*);
  void addAFollowing(std::string, std::string);
  void databaseDump(std::string);
  void sccDump(std::string);
  void DFS(User*, int&);
  void createTrendingHeap();
  void Trending(int n);
  bool login(std::string username, std::string password);
  void logout();

 private:
  /* Add any other data members or helper functions here  */
  std::map<std::string, User*> allUsers; 
  std::map<User*, unsigned int> allPasswords; 
  std::map<std::string, std::set<Tweet*> > allHashtags; 
  std::map<std::string, std::set<Tweet*> > allMentions; 
  std::stack<User*> mainStack;
  std::set<User*> seenSet;
  std::vector<std::set<User*> > connComps;
  Heap<TagData, TagStringEqual, TagIntGreater, TagStringHasher> trending_;
  std::string currUser;
};


#endif

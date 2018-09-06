#ifndef PAGE_H
#define PAGE_H
#include <string>
using std::string;
#include<vector>
using std::vector;

class Page { 
public:
  Page(int i,const string &u);//implement ths in the page.cpp
  int getID() const { return id; }//Represnets the page ID
  string getURL() const { return url;}//Represnts page URL
  double getRank() const { return rank; }
  void addLink(int id);//implement this in the page.cpp 
  void setRank(double r) { rank = r;}
  vector<int> &getLinks() { return links; };//Models the outbound links of the page 
private:
  int id;
  string url;
  double rank;
  vector<int> links;
};  
#endif
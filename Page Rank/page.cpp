#include <iostream> 
#include "page.h"


Page::Page(int i, const string &u)
{
	id = i; 
	url = u;  
}

void Page::addLink(int id)
{
	links.push_back(id); 	
}
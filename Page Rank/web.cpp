#include "web.h"
#include "page.h"


Web::Web()
{
	//set web to nothing 
}

Web::~Web()
{
	//set destructor to nothing
}

//read from the graph text file 
bool Web::read_graph(const char *filename)
{
	//set up ifstream, checking if it fails 
	ifstream ifile(filename);
	int numPages;
	if (ifile.fail())
	{
		cout << "Something went wrong" << endl;
		return 0; 
	}

	ifile >> numPages; 
	if (ifile.fail())
	{
		cout << "Something went wrong" << endl;
		return 0; 
	}


	int id;
	string buffer;
	string url; 
	double rank;

	//For loop to populate variables by reading from file
	//Those variables will then be used to create the page objects 
	for (int i = 0; i < numPages; i++)
	{
		//Getting info needed for page constructor 
		ifile >> id;
		ifile >> url; 
		Page webPage(id, url);

		//Getting rank for page 
		ifile >> rank; 
		webPage.setRank(rank);

		//Getting outgoing links for the page
		getline(ifile, buffer);
		getline(ifile, buffer);
		stringstream ss(buffer);

		while (ss >> id)
		{
			webPage.addLink(id);
		}

		//Page is all set up, push it into the vector
		pages.push_back(webPage);
	}
	return true; 
}

//write to a graph text file 
bool Web::write_graph(const char *filename)
{
	ofstream ofile(filename);
	ofile << pages.size() << endl;

	int id; 
	string url;
	double rank; 

	//for loop that prints the ID, URL, Rank, and outgoing links for each page
	//all this info is written to a graph text file 
	for (int i = 0; i < pages.size(); i++)
	{
		id = pages[i].getID(); 
		ofile << id << endl;

		url = pages[i].getURL();
		ofile << "\t" << url << endl;

		rank = pages[i].getRank();
		ofile << "\t" << rank << endl;

		vector<int> &links = pages[i].getLinks();

		ofile << "\t";
		for (int i = 0; i < links.size(); i++)
		{
			ofile << links[i] << " ";
		}
		ofile << endl; 
	}
	return true; 
}

//calculate the rank of each page 
void Web::calculate_rank(int S, int N)
{ 
	for (int i = 0; i < pages.size(); i++)//Dispersing walkers amongst the pages
	{
		//Each iteration of the for loop will give a walker an ID of a page
		for (int j = 0; j < N/pages.size(); j++)
		{
			walkers.push_back(i);
		}
	}

	//loop that runs through simulations to see where the walkers end up 
	for (int i = 0; i < S; i++)
	{
		for (int k = 0; k < N; k++)
		{
			//each walker chooses outgoing links from the page its on randomly
			vector<int> links = pages[walkers[k]].getLinks();
			int idIndex = rand()%links.size();
			walkers[k] = links[idIndex];
		}
	}
	//loop to figure out the proportion of walkers on each page at the end 
	for (int j = 0; j < pages.size(); j++)
	{
		double prop = 0;
		for (int z = 0; z < N; z++)
		{
			if (walkers[z] == j)
			{
				prop++;
			}
		}
		pages[j].setRank(prop/N); 
	}
}
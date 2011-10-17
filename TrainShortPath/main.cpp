/* c3109810	Liam Sanders

Shortest path between 2 stations using Dijkstras algorithim.

*/

//Needed includes for input/output and string parsing
#include <iostream>
#include <string>
#include <vector>

//TinyXML requirements, note that this is not my code.
#ifdef TIXMLUSESTL
#include <iostream>
#include <sstream>
using namespace std;
#else
#include <stdio.h>
#endif

#if defined( WIN32 ) && defined( TUNE )
#include <crtdbg.h>
CrtMemState startMemState;
CrtMemState endMemState;
#endif

#include "xml\tinyxml.h"

class StationEdge
{
	string Name;
	string Line;
	int Duration;
	public:
		void set_edge(string sname,string sline,int dur)
		{
			Name = sname;
			Line = sline;
			Duration = dur;
		}
};
class Station
{

	public:
		void set_station(string sname,string sline,vector<StationEdge> vedges)
		{
			Name = sname;
			Line = sline;
			StationEdges = vedges;
		}
};

using namespace std;

//The total number of stations, 
//The most changes that occur at any one station (ie the most edges to any one vertex)
//A large int, large enough such that any edge has a weight less than it.
static const int total_stations = 11;
static const int max_change = 3;
static const int bigint = 9001;

string enames;
string elines;

//we will be using an adjacency matrix to denote the graph.
int edge_matrix[total_stations][total_stations];

//These store the names of the stations, which line that station is on and the names and lines of each station connecting to it
vector<Station> stations;

//used to convert the XML input to the adjacency matrix
int weights[total_stations][max_change];

//stores closest predecessor to the node.
int predecessor_s[total_stations];


void initialize()
{
	//Load XML into memory (taken and modified from xmltest.cpp)
	TiXmlDocument doc("RailNetwork.xml");
	if (doc.LoadFile()){
		
		TiXmlNode* root;
		root = doc.RootElement();

		for(TiXmlNode* node = root->FirstChild(); node; node = node->NextSibling() )
		{
			vector<StationEdge> tempedges;
			TiXmlNode *name = node->FirstChild("Name")->FirstChild();
			//station_names.push_back(name->Value());

			TiXmlNode *line = node->FirstChild("Line")->FirstChild();
			//station_line.push_back(line->Value());

			TiXmlNode *edges = node->FirstChild("StationEdges");

			for(TiXmlNode* edge = edges->FirstChild("StationEdge"); edge; edge = edge->NextSibling() )
			{
				TiXmlNode *ename = edge->FirstChild("Name")->FirstChild();
				//enames[i][j] = ename->Value();

				TiXmlNode *eline = edge->FirstChild("Line")->FirstChild();
				//elines[i][j] = eline->Value();

				TiXmlNode *duration = edge->FirstChild("Duration")->FirstChild();
				//weights[i][j] = atoi(duration->Value());
				tempedges.push_back(
			}	

		}


	}
	//From here on all code was written by me.

	//Create adjacency matrix, prepare it for dijkstra's algorithm
	for (int i=0;i<total_stations;i++)
	{
		for (int j=0;j<total_stations;j++)
		{

			for (int x=0;x<max_change;x++)
			{
				if	(station_names[j] == enames[i][x] && station_line[j] == elines[i][x])
				{
					edge_matrix[i][j] = weights[i][x];
				}
			}
			if(edge_matrix[i][j] == 0)
				edge_matrix[i][j] = bigint; //we need what would be 0 weights to have a "big" weight so the algorithim doesnt use them.
		}
	}
}

//dijkstras algorithim specifying the starting node.
void dijkstra(int start_node)
{
	int length[total_stations];
	bool visited[total_stations];
	int count=0;

	//Initialize all stations to not visited, and the shortest distance to each station is the maximum distance
	for (int i=0;i<total_stations;i++)
	{
		visited[i] = false;
		length[i] = bigint;
		predecessor_s[i] = -1;
	}
	
	//the distance from the starting node to itself is 0.
	length[start_node] = 0;

	while(count<total_stations) 
	{
		//We will now find the closest unmarked node to the source
		int closeunmark;
		int smalllength = bigint;

		//Loop through the nodes to find the closest
		for (int i = 0; i<total_stations; i++)
		{
			if(!visited[i] && smalllength >= length[i])
			{
				smalllength = length[i];
				closeunmark = i;
			}
		}

		// we now consider that node visited
		visited[closeunmark] = true;

		//Find the shortest distance from this node to every other node, take a "step" in that direction. Mark this node as a predecessor
		for(int i=0;i<total_stations;i++) 
		{
			if(!visited[i] && edge_matrix[closeunmark][i]) 
			{
				if(length[i] > (length[closeunmark] + edge_matrix[closeunmark][i])) 
				{
					length[i] = length[closeunmark] + edge_matrix[closeunmark][i];
					predecessor_s[i] = closeunmark;
				}
			}
		}// traverse all stations
	count++;
	}
}

//Print the route required to travel recursivly
//Note. When changing stations it lists the same station and the same line 2x.
void printPath(int end_node,int start_node,int time)
{
	if(start_node == end_node){
		cout<<"Total time: "<<time<<endl;
		cout<<"Starting at "<<station_names[end_node]<<" take line "<<station_line[start_node]<<endl;
	}
	else
	{
		time = time + edge_matrix[predecessor_s[end_node]][end_node];
		printPath(predecessor_s[end_node],start_node,time);
		cout<<"Then take line "<<station_line[predecessor_s[end_node]]<<" to "<<station_names[end_node]<<endl;
	}
	
}

//Main function
int main()
{
	//read xml, setup arrays
	initialize();

	//Get user data, Validate.
	string start_station;
	string end_station;
	int start_node;
	int end_node;
	int choice;

	cout << "Enter the name of the starting station: ";
	getline(cin,start_station);
	//start_station = "Summer Hill";
	cout << "Enter the name of the ending station: ";
	getline(cin,end_station);
	//end_station = "Homebush";
	
	bool start_exists = false;
	bool end_exists = false;
	for (int i=0;i<total_stations;i++)
	{
		if(start_station == station_names[i])
		{
			choice = 0;
			
			//If the user wishes to specify which line they travel on
			if(start_exists == true)
			{
				cout<<"Please choose a line. 1 for Inner West Line, 2 for South Line:";
				cin>>choice;
				if(choice == 2)
				{
					start_node = i;
				}
			}
			else
			{
				start_exists = true;
				start_node = i;
			}
		}
		else if(end_station == station_names[i])
		{
			choice = 0;
			if(end_exists == true)
			{
				cout<<"Please choose a line. 1 for Inner West Line, 2 for South Line:";
				cin>>choice;
				if(choice == 2)
				{
					end_node = i;
				}
			}
			else
			{
				end_exists = true;
				end_node = i;
			}
		}
	}
	if(start_exists)
	{
		if(end_exists)
		{
			cout<<"Stations found. Begining algorithim"<<endl;
			dijkstra(start_node);
			printPath(end_node,start_node,0);
			cin.get();
		}
		else
		{
			cout<<"End station not found. Terminating"<<endl;
			exit(1);
		}
	}
	else
	{
		cout<<"End station not found. Terminating"<<endl;
		exit(1);
	}
	return 0;
}
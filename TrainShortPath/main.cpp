/* c3109810	Liam Sanders

Shortest path between 2 stations using Dijkstras algorithim.

*/

//Needed includes for input/output and string parsing
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Station.h"
#include "Edges.h"

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

#include "xml/tinyxml.h"
//end

using namespace std;

string enames;
string elines;

//we will be using an adjacency matrix to denote the graph.
//int edge_matrix[total_stations][total_stations];
static const int bigint = 9001;

//These store the names of the stations, which line that station is on and the names and lines of each station connecting to it
vector<Station> stations;
vector<int> distanceFromStart;

//used to convert the XML input to the adjacency matrix
//int weights[total_stations][max_change];

class Node
{
public:
	int node;
	int distance;
};
bool operator> (const Node& patha,const Node &pathb)
{
	return patha.distance < pathb.distance;
}
bool operator< (const Node& patha,const Node &pathb)
{
	return patha.distance > pathb.distance;
}

void initialize()
{
	//Load XML into memory (taken and modified from xmltest.cpp)
	TiXmlDocument doc("RailNetwork.xml");
	if (doc.LoadFile()){
		
		TiXmlNode* root;
		root = doc.RootElement();

		for(TiXmlNode* node = root->FirstChild(); node; node = node->NextSibling() )
		{
			vector<Edges> tempedges;
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
				
				tempedges.push_back(Edges(ename->Value(),eline->Value(),atoi(duration->Value())));
			}	
			stations.push_back(Station(name->Value(),line->Value(),tempedges));
		}


	}
	//From here on all code was written by me.
}

//dijkstras algorithim specifying the starting node.
void dijkstra(int start_node)
{
	priority_queue<Node> dijpath;
	vector<int> predecessor;
	
	Node start;

	start.distance = 0;
	start.node = start_node;

	//Initialize all stations to not visited, and the shortest distance to each station is the maximum distance
	dijpath.push(start);
	
	for (int i=0;i<stations.size();i++)
	{
		distanceFromStart.push_back(bigint);
		predecessor.push_back(-1);
	}

	//the distance from the starting node to itself is 0.
	distanceFromStart.at(start_node) = 0;

	while(!dijpath.empty())
	{
		int nextdist = bigint;
		Node current = dijpath.top();
		if(current.distance >distanceFromStart.at(current.node))
		{
			continue;
		}

		dijpath.pop();


		for(int i=0; i < stations.at(current.node).getEdgeCount(); i++) // go though all the connected edges
		{
		for (int j = 0;j<stations.size();j++)
		{
			if(stations.at(current.node).getName() == stations.at(j).getName() && stations.at(current.node).getLine() == stations.at(j).getLine())
				cout<<j;

		}
			cout <<distanceFromStart.at(current.node)<<" "<<stations.at(current.node).getEdgeWeight(i)<<" "<<distanceFromStart.at(i);
			if(distanceFromStart.at(i)>distanceFromStart.at(current.node)+stations.at(current.node).getEdgeWeight(i))
			{
				for (int j = 0;j<stations.size();j++)
				{
					if(stations.at(i).getName() == stations.at(j).getName() && stations.at(i).getLine() == stations.at(j).getLine())
					{
						distanceFromStart.at(current.node) = distanceFromStart.at(current.node) + stations.at(current.node).getEdgeWeight(i);

						Node newNode;
						newNode.distance = distanceFromStart.at(current.node);
						predecessor.at(current.node) = j;
						newNode.node = j;
						dijpath.push(newNode);
					}
				}
			}
		}
	}
}


//Print the route required to travel recursivly
//Note. When changing stations it lists the same station and the same line 2x.
/*
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
	
}*/

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

	cout << "Enter the name of the starting station: ";
	//getline(cin,start_station);
	start_station = "Summer Hill";
	cout << "Enter the name of the ending station: ";
	//getline(cin,end_station);
	end_station = "Homebush";
	
	bool start_exists = false;
	bool end_exists = false;
	for (int i=0;i<stations.size();i++)
	{
		if(start_station == stations.at(i).getName())
		{
			start_node = i;
			start_exists = true;
		}
		else if(end_station == stations.at(i).getName())
		{
			end_exists = true;
			end_node = i;
		}
	}
	if(start_exists)
	{
		if(end_exists)
		{
			cout<<"Stations found. Begining algorithim"<<endl;
			dijkstra(start_node);
			//printPath(end_node,start_node,0);
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

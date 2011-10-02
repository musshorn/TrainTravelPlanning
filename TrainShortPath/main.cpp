#include <iostream>
#include <string>

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

using namespace std;

static const int total_stations = 11;
static const int max_change = 3;
static const int bigint = 9001;

int edge_matrix[total_stations][total_stations];
int vertex[total_stations];
string station_names[total_stations];
string station_line[total_stations];
string enames[total_stations][max_change];
string elines[total_stations][max_change];
int weights[total_stations][max_change];
bool visited[total_stations];
int length[total_stations];
int predecessor_s[total_stations];

void initialize()
{
		//Load XML into memory
	TiXmlDocument doc("RailNetwork.xml");
	if (doc.LoadFile()){
		
		TiXmlNode* root;
		root = doc.RootElement();

		int i=0;
		for(TiXmlNode* node = root->FirstChild(); node; node = node->NextSibling() )
		{
			TiXmlNode *name = node->FirstChild("Name")->FirstChild();
			station_names[i] = name->Value();

			TiXmlNode *line = node->FirstChild("Line")->FirstChild();
			station_line[i] = line->Value();

			TiXmlNode *edges = node->FirstChild("StationEdges");
			int j =0;
			for(TiXmlNode* edge = edges->FirstChild("StationEdge"); edge; edge = edge->NextSibling() )
			{
				TiXmlNode *ename = edge->FirstChild("Name")->FirstChild();
				enames[i][j] = ename->Value();

				TiXmlNode *eline = edge->FirstChild("Line")->FirstChild();
				elines[i][j] = eline->Value();

				TiXmlNode *duration = edge->FirstChild("Duration")->FirstChild();
				weights[i][j] = atoi(duration->Value());
				j++;
			}	
			i++;
		}

	}
/*	for (int i=0;i<total_stations;i++)
	{
		cout << station_names[i]<<endl;
	}*/
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
				edge_matrix[i][j] = bigint;
		}
	}
/*	for (int i=0;i<total_stations;i++)
	{
		for (int j=0;j<total_stations;j++)
		{
			cout<<edge_matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	*/
}

int getunmarked()
{
	int smalllength = bigint;
	int closeunmark;

	for (int i = 0; i<total_stations; i++)
	{
		if(!visited[i] && smalllength >= length[i])
		{
			smalllength = length[i];
			closeunmark = i;
		}
	}
	
	return closeunmark;
}

void dijkstra(int start_node)
{
	int count=0;

	for (int i=0;i<total_stations;i++)
	{
		visited[i] = false;
		length[i] = bigint;
		predecessor_s[i] = -1;
	}

	length[start_node] = 0;
	while(count<total_stations) 
	{
		int closeunmark = getunmarked();
		visited[closeunmark] = true;
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
		}
	count++;
	}
}

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
/*	for (int i=0;i<end_node;i++)
	{
		if(predecessor_s[i] == -1)
			cout<<"Done";
		else if (i==0)
			cout<<"From "<<station_names[start_node]<<" take line "<<station_line[predecessor_s[start_node]]<<" to station "<<station_names[total_stations - predecessor_s[i]]<<endl;
		else
			cout<<"Then change to line "<<station_line[predecessor_s[i]]<<" and continue to "<<station_names[predecessor_s[i]]<<endl;
	}*/
	
}

int main()
{
	initialize();

	//Get user data, Validate.
	string start_station;
	string end_station;
	int start_node;
	int end_node;
	int choice;
	cout << "Enter the name of the starting station: ";
	//getline(cin,start_station);
	start_station = "Summer Hill";
	cout << "Enter the name of the ending station: ";
	//getline(cin,end_station);
	end_station = "Ashfield";
	
	bool start_exists = false;
	bool end_exists = false;
	for (int i=0;i<total_stations;i++)
	{
		if(start_station == station_names[i])
		{
			choice = 0;
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
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
			for(TiXmlNode* edge = edges->FirstChild(); edge; edge = edge->NextSibling() )
			{
				TiXmlNode *ename = edge->FirstChild("Name")->FirstChild();
				enames[i][j] = ename->Value();

				TiXmlNode *eline = edge->FirstChild("Line")->FirstChild();
				elines[i][j] = eline->Value();

				TiXmlNode *duration = edge->FirstChild("Duration")->FirstChild();
				weights[i][j] = atoi(duration->Value());
				//cout<<ename->Value()<<endl;
				j++;
			}	
			i++;
		}

	}
	for (int i=0;i<total_stations;i++)
	{
		cout << station_names[i]<<endl;
	}
	//Create adjacency matrix, prepare it for dijkstra's algorithm
	for (int i=0;i<total_stations;i++)
	{
		for (int j=0;j<total_stations;j++)
		{

			for (int x=0;x<max_change;x++)
			{
				if	(station_names[j] == enames[i][x] && station_line[j] == elines[i][x])
				{
					edge_matrix[i][j] = weights[j][x];
				}
			}
			if(edge_matrix[i][j] == 0)
				edge_matrix[i][j] = bigint;
		}
	}
}
void dijkstra(int start_i,int end_i)
{
	bool visited[total_stations];
	int distance[total_stations];
	int predecessor[total_stations];
	int current = start_i;
	int count=0;

	cout<<start_i<<" "<<end_i<<endl;

	for (int i=0;i<total_stations;i++)
	{
		visited[i] = false;
		distance[i] = bigint;
		predecessor[i] = 0;
	}
	distance[start_i] = 0;
	visited[start_i] = true;

	int dist = distance[current];
	int smalldist =	bigint;
	int closeunmark;
	while(count<total_stations)
	{
		for (int i = 0; i<total_stations; i++)
		{
			if(!visited[i] && smalldist >= distance[i])
			{
				smalldist = distance[i];
				closeunmark = i;
			}
		}
		for (int i = 0; i<total_stations; i++)
		{
			visited[closeunmark] = true;

		}
	}


	cout<<"The shortest path is: "<<endl;
	//for (int i=1;i<5;i++)
	//	cout<<station_names[predecessor[i]] << " -> " << station_names[predecessor[i-1]] <<endl;
	for (int i=0;i<total_stations;i++)
	{
		cout<<station_names[predecessor[i]] <<"\t" << distance[i]<< endl;
	}

	//cin.get();
}
int main()
{
	initialize();

	//Get user data, Validate.
	string start_station;
	string end_station;
	int start_i;
	int end_i;
	cout << "Enter the name of the starting station: ";
	//cin >> start_station;
	start_station = "Homebush";
	cout << "Enter the name of the ending station: ";
	//cin >> end_station;
	end_station = "Ashfield";
	
	bool start_exists = false;
	bool end_exists = false;
	for (int i=0;i<total_stations;i++)
	{
		if(start_station == station_names[i])
		{
			start_exists = true;
			start_i = i;
		}
		else if(end_station == station_names[i])
		{
			end_exists = true;
			end_i = i;
		}
	}
	if(start_exists)
	{
		if(end_exists)
		{
			cout<<"Stations found. Begining algorithim"<<endl;
			dijkstra(start_i,end_i);
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

/*	INT_MAX is a big number.
	for (int i=0;i<total_stations;i++)
	{
		for (int j=0;j<total_stations;j++)
		{
			cout<<edge_matrix[i][j]<<" ";
		}
		cout<<endl;
	}*/
	return 0;
}
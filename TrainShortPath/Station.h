#ifndef STATION
#define STATION
#include <vector>
#include <string>
#include "Edges.h"

class Station
{
	public:
		Station(std::string name, std::string line, std::vector<Edges> edge);
		std::string getName();
		std::string getLine();
		std::string Station::getEdgeName(int id);
		std::string Station::getEdgeLine(int id);
		int getEdgeCount();
		int getEdgeWeight(int id);
		std::vector<Edges> getEdges();
	private:
		std::string Name;
		std::string Line;
		std::vector<Edges> Edge;
};
#endif
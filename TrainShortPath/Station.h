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
		int getEdgeCount();
		int getEdgeWeight(int id);
	private:
		std::string Name;
		std::string Line;
		std::vector<Edges> Edge;
};
#endif
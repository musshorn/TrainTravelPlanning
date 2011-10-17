#ifndef STATION
#define STATION
#include <vector>
#include <string>
#include "Edges.h"

class Station
{
	public:
		Station(string name, string line, std::vector<Edges> edge);
		~Station(void);
	private:
		string Name;
		string Line;
		std::vector<Edges> Edge;
};
#endif
#include <vector>
#include <string>
#include "Station.h"

Station::Station(std::string sname, std::string sline, std::vector<Edges> sedges)
{
	Name = sname;
	Line = sline;
	Edge = sedges;
}
std::string Station::getName()
{
	return Name;
}
int Station::getEdgeCount()
{
	return Edge.size();
}
int Station::getEdgeWeight(int id)
{
	return Edge.at(id).getDuration();
}
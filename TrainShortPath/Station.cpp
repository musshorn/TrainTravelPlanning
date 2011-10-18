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
std::string Station::getLine()
{
	return Line;
}
int Station::getEdgeCount()
{
	return Edge.size();
}
int Station::getEdgeWeight(int id)
{
	return Edge.at(id).getDuration();
}
std::vector<Edges> Station::getEdges() 
{
	return Edge;
}
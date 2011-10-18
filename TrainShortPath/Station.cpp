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
std::string Station::getEdgeName(int id)
{
	return Edge.at(id).getName();
}
std::string Station::getEdgeLine(int id)
{
	return Edge.at(id).getLine();
}
std::vector<Edges> Station::getEdges() 
{
	return Edge;
}
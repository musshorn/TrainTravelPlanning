#include <vector>
#include <string>
#include "Station.h"

Station::Station(std::string sname, std::string sline, std::vector<Edges> sedges)
{
	Name = sname;
	Line = sline;
	Edge = sedges;
}
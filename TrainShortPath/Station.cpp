#include <vector>
#include <string>
#include "Station.h"

Station::Station(string sname, string sline, std::vector<Edges> sedges)
{
	Name = sname;
	Line = sline;
	Edge = sedges;
}
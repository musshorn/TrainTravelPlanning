#include <string>
#include "Edges.h"

Edges::Edges(std::string ename, std::string eline, int eduration)
{
	Name = ename;
	Line = eline;
	Duration = eduration;
}
int Edges::getDuration()
{
	return Duration;
}
std::string Edges::getName()
{
	return Name;
}
std::string Edges::getLine()
{
	return Line;
}
#ifndef EDGES
#define EDGES

#include <string>

class Edges
{
	public:
		Edges(std::string ename, std::string eline, int eduration);
		int getDuration();
		std::string getName();
		std::string getLine();
	private:
		std::string Name;
		std::string Line;
		int Duration;
};
#endif
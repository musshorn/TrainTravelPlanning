#ifndef EDGES
#define EDGES

#include <string>

class Edges
{
	public:
		Edges(std::string ename, std::string eline, int eduration);
		~Edges(void);
	private:
		string Name;
		string Line;
		int Duration;
};
#endif
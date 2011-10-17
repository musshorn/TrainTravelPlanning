#ifndef EDGES
#define EDGES

#include <string>

class Edges
{
	public:
		Station(void);
		~Station(void);
	private:
		string Name;
		string Line;
		int Duration;
};
#endif
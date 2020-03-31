#ifndef DIE_H
#define DIE_H

#include <string>
#include <sstream>
using namespace std;

class Die  {
private:
	string dieSide;
	char randSide;

public:
	Die();
	~Die();
	string getDie();
	char rollDie();
	
};
#endif // !DIE_H


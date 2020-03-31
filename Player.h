#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
private:
	string playerName;
	int playerChips;
public:
	Player(string);
	~Player();
	void setChips(int);
	string getName();
	int getChips();
	void minusOneChips();
	void plusOneChips();
};

#endif // !PLAYER_H


#include "Die.h"

Die::Die() {

}

Die::~Die() {

}

string Die::getDie() {
	stringstream displayDie;
	
	displayDie <<
		"\n . --- . " <<
		"\n :  " << dieSide << "  : " <<
		"\n ` --- ` ";

	return displayDie.str();
}

char Die::rollDie() { 
	char dieSides[6] = { 'L','C','R','O','O','O' };
	randSide = dieSides[rand() % 6];

	if (randSide == 'L') {
		dieSide = "L";
	}
	else if (randSide == 'C') {
		dieSide = "C";
	}
	else if (randSide == 'R') {
		dieSide = "R";
	}
	else if (randSide == 'O') {
		dieSide = "O";
	}
	else {
		dieSide = "error";
	}

	return randSide;
}

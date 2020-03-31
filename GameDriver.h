#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H

#include "Player.h"
#include "Die.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
using namespace std;

int runGameMenu();
void displayGameRules();
void gameSetup(int&, int&, int&, int&, char&, int&, vector <Player*>&, vector <Player*>&);
int runGame();
vector <Player*> createPlayers(int);
vector <Player*> createComputers(int);
bool checkGameOver(vector <Player*>, int);
void dieAction(vector <Player*>, Player&, int, int, char);
void dieActionReverse(vector <Player*>, Player&, int, int, char);

#endif // !GAMEDRIVER_H


/*
Full Name		: Adeline Soerjonoto
Student ID		: 30849756
Units			: MCD4720 - Fundamentals of C++
Date Created	: 25 August 2019
Last Updated	: 12 September 2019
Lecturer Name	: Haidar AL-Khalidi
Lab Teacher Name: Mehran Vahid
Lab No.			: MCD4720 Laboratory 07-P1
Lab Time		: Wednesday, 1:00pm - 3:30pm
Desciption		:
This program is for Assignment 3 MCD4720 (Thursday, 12 September 2019, 7:55 PM)
It runs a program to play the LCR game. The arrange of the seat is clockwise, so the left of player 1 is 2.
The extra functionality for the program is in the ExtraFunctionality.txt
*/
#include "GameDriver.h" // include all header from GameDriver.h

/*
Function Name	= main
Input(s)		= -
Output(s)		= -
Descriptions	=
The main function wil run the runGameMenu function.
*/
int main() {
	runGameMenu();
	system("pause");
	return 0;
}

/*
Function Name	= runGameMenu
Input(s)		= option
Output(s)		= the game menu
Descriptions	=
The function displays the menu and asks for an option from the menu.
*/
int runGameMenu() {
	int option;
	while (true) {
		system("CLS");
		
		//The Game Menu
		cout << 
			"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " <<
			"\n                - LCR GAME -                " <<
			"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " <<
			"\n  Choose between option [1-3]" <<
			"\n  [1] Display the rules of the game " <<
			"\n  [2] Play the game" <<
			"\n  [3] Exit the game" <<
			"\n " <<
			"\n  Your Option : ";
		cin >> option;

		//Option Rsult
		switch (option) {
		case 1: displayGameRules(); break; //go to the funtion that display the rules
		case 2: runGame(); break; // go to the function that runs the game to play
		case 3: return 0; // exit the program
		default: break;
		}
	}
}

/*
Function Name	= displayGameRules
Input(s)		= -
Output(s)		= Information from filename (GameRules.txt)
Descriptions	=
Function for displaying about the information about the LCR game from GameRules.txt
The information is about how to play the game and the rules
*/
void displayGameRules() {
	ifstream gameRules;
	string text;
	gameRules.open("GameRules.txt");

	//Display the introduction and the rules of the LCR game
	cout << endl <<
		"  ------------------------------------------------------------------ \n" <<
		"                              Game Rules                            \n" <<
		"  ------------------------------------------------------------------ \n";
	if (gameRules.is_open()) {
		while (!gameRules.eof()) {
			getline(gameRules, text);
			cout <<"   "<< text << endl;
		}
	}
	else {
		cout << "  The file for Game Rules is not open" << endl;
	}
	
	gameRules.close();

	system("pause");
	system("CLS");
}

/*
Function Name	= gameSetup
Input(s)		= number of player and computer, player's name, chips, and game effect
Output(s)		= the game setup
Descriptions	=
It ask the use to input number of player and computer, player's name, chips, and game effect by calling other function
The game effect can be normal or reverse.
*/
void gameSetup(int& numPlayers, int& numChips, int& numComputers, int& numAllPlayers, char& gameEffect, int& chipsForPot, vector <Player*>& allPlayers, vector <Player*>& allComputers) {
	
	//Display the game setup before playing the game
	cout << endl <<
		"  -------------------------------------------------- \n" <<
		"                      Game Setup                     \n" <<
		"  -------------------------------------------------- \n";
	cout <<
		"  The number of players and computers is minimum 3\n" <<
		"  The number of chips should at least equal to the\n" <<
		"  the number of all players and computers \n";
	while (true) {
		cout << "  o Number of Players = ";
		cin >> numPlayers; //input the number of player
		allPlayers = createPlayers(numPlayers);
		cout << "  o Number of Computers = ";
		cin >> numComputers;//input the number of computer player
		allComputers = createComputers(numComputers);
		numAllPlayers = numPlayers + numComputers;
		if (numAllPlayers < 3) { // The game need at least 3 player, if the user put below 3, it will ask to input again
			cout << "  ~ The total number of players and computers is below 3.\n" <<
				"    Input again ~ " << endl;
		}
		else {
			break;
		}
	}
	while (true) {
		cout << "  o Number of Chips = ";
		cin >> numChips; //input the number of chips each player and pot
		if (numChips < numAllPlayers) {
			cout << "  ~ The number of chips is below the number of \n" <<
				"    players and computers. Input again ~ " << endl;
		}
		else {
			break;
		}
	}
	while (true) {
		char inputGameEff;
		cout << "  o [N]ormal or [R]everse = "; //Ask the user for game effect (Normal or Reverse)
		cin >> inputGameEff;

		if (inputGameEff == 'N' || inputGameEff == 'n') {
			gameEffect = 'N';
			break;
		}
		else if (inputGameEff == 'R' || inputGameEff == 'r') {
			gameEffect = 'R';
			while (true) {
				cout <<
					"  o Chips into pot from each player \n" <<
					"    (must be smaller than the number of chips)= ";
				cin >> chipsForPot;
				if (chipsForPot >= numChips) {
					cout << "  ~ The number of chips into pot from player is \n" <<
						"    too big. Input again ~ " << endl;
				}
				else {
					break;
				}
			}
			break;
		}
		else {
			cout << "Choose between [N]ormal or [R]everse." << endl;
		}
	}
}

/*
Function Name	= runGame
Input(s)		= -
Output(s)		= the game (all player name with chips, dice, the winner)
Descriptions	=
Function for running the LCR game.
Runs the gameSetup function to set all the game's components
After that, it displays all information for all participant and roll 3 dice for each parcticipant's turn.
The game will end if there is only one player. It will be done by other function for checking the game over conditions 
*/
int runGame() {
	srand((unsigned)time(NULL));
	int numPlayers, numChips, numComputers, noDice, chipsPlayer, potChips, numAllPlayers, chipsForPot;
	int winnerScore = 0;
	string winnerName = " ";
	char gameEffect, option, temp;
	bool gameOver = true;
	int const maxNumDice = 3;
	vector <Player*> allPlayers, allComputers;
	vector <Die*> allDice;
	vector <char> tempDice;

	//Create dice
	for (int dice = 0; dice < maxNumDice; dice++) {
		Die* pDie = new Die();
		allDice.push_back(pDie); // input all dice into a vector according to the number of die
	}
	
	//Display the game setup for the user to set the game's components
	gameSetup(numPlayers, numChips, numComputers, numAllPlayers, gameEffect, chipsForPot, allPlayers, allComputers);
	
	//Insert computer vector into all player vector
	allPlayers.insert(allPlayers.end(), allComputers.begin(), allComputers.end());
	Player pot("POT");// create pot

	//Set the number of chips to all the player and pot
	if (gameEffect == 'N') {
		chipsPlayer = numChips;
		potChips = 0;
	}
	else if (gameEffect == 'R') {
		chipsPlayer = numChips - chipsForPot;
		potChips = (chipsForPot * numAllPlayers);
	}
	else { cout << "Error" << endl; }
	for (int counter = 0; counter < numAllPlayers; counter++) {
		allPlayers[counter]->setChips(chipsPlayer);
	}
	pot.setChips(potChips);

	system("pause");

	int playerTurn = rand() % numAllPlayers; // randomly choose the player who will play first

	//The Game Driver
	while (true) {
		while (playerTurn < numAllPlayers) {// the loop for player's turn in the game
			system("CLS");

			//Checking whether the condition for game over is met
			gameOver = checkGameOver(allPlayers, numAllPlayers);

			cout <<
				"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " <<
				"\n                - LCR GAME -                " <<
				"\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " <<
				"\n " << pot.getName() << "\t = " << pot.getChips() << " chips";
			for (int counter = 0; counter < numAllPlayers; counter++) {
				cout << "\n " << allPlayers[counter]->getName() << "\t = " << allPlayers[counter]->getChips() << " chips";
			}
			cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ";

			//The game will end if the condition for game over is met
			if (!gameOver) {
				break;
			}

			//The number of dice to roll is according to the number chips, with maximum number of dice is 3
			if (allPlayers[playerTurn]->getChips() > maxNumDice) {
				noDice = maxNumDice;
			}
			else {
				noDice = allPlayers[playerTurn]->getChips();
			}

			if (noDice != 0) {
				cout << "\n It's your turn, " << allPlayers[playerTurn]->getName() << endl;
			}
			else {
				cout << "\n Skip " << allPlayers[playerTurn]->getName() << "'s turn , go to the next player. ";
			}

			//Ask the user if the user wants to quit the game
			if (playerTurn <= (numPlayers - 1)) {
				while (true) {
					cout << "\n  Do you want to [Q]uit or [R]oll ? ";
					cin >> option;
					if (option == 'Q' || option == 'q') {
						cout << endl;
						system("pause");
						return 0;
					}
					else if (option == 'R' || option == 'r') {
						break;
					}
					else {
						cout << "  Choose an option between Q or R. " << endl;
					}
				}
			}

			for (int dice = 0; dice < noDice; dice++) {
				tempDice.push_back(allDice[dice]->rollDie());
				cout << allDice[dice]->getDie();
			}
			cout << endl << endl;
			for (int dice = 0; dice < noDice; dice++) {
				temp = tempDice[dice];
				if (gameEffect == 'N') {
					dieAction(allPlayers, pot, playerTurn, numAllPlayers, temp);
				}
				else if (gameEffect == 'R') {
					dieActionReverse(allPlayers, pot, playerTurn, numAllPlayers, temp);
				}
				else { cout << "Error" << endl; }
			}
			cout << endl;

			//Clearing the vector for dice
			tempDice.clear();
			playerTurn++;

			system("pause");
		}

		playerTurn = 0; // The turn is back to the first player
		
		//The condition of the game over is met, the game is finish
		if (!gameOver) {
			cout << "\n The Game is finish" << endl;
			break;
		}
	}

	//Checking the player who win the game
	for (int counter = 0; counter < numAllPlayers; counter++) {
		if (allPlayers[counter]->getChips() != 0) {
			winnerName = allPlayers[counter]->getName();
			winnerScore = allPlayers[counter]->getChips();
			winnerScore += pot.getChips();
		}
	}

	//Displaying the winner of the game
	cout << endl <<
		"  ----------------------------- \n" <<
		"       Winner : " << winnerName << "    \n" <<
		"       Score  : " << winnerScore << "    \n" <<
		"  ----------------------------- \n";

	//Delete all objects in the heap along with pointers
	for (int counter = 0; counter < allPlayers.size(); counter++) {
		delete allPlayers[counter];
		allPlayers[counter] = NULL;
	}
	for (int dice = 0; dice < maxNumDice; dice++) {
		delete allDice[dice];
		allDice[dice] = NULL;
	}

	system("pause");
	return 0;
}

/*
Function Name	= createPlayer
Input(s)		= player's name
Output(s)		= -
Descriptions	=
Function for creating players and put it in a vector
*/
vector <Player*> createPlayers(int numPlayerInput) {
	string playerName;
	vector <Player*> createPlayerVector;

	//Create players according to the input. Insert all players into a vector
	for (int count = 0; count < numPlayerInput; count++) {
		cout << "    -   Player " << count+1 << " name = ";
		cin >> playerName;
		Player* pPlayer = new Player(playerName);// create player
		createPlayerVector.push_back(pPlayer); // put the player into vector
	}

	return createPlayerVector;
}

/*
Function Name	= createComputer
Input(s)		= -
Output(s)		= -
Descriptions	=
Function for creating computer players and put it in a vector
*/
vector <Player*> createComputers(int numComputerInput) {
	string computerName;
	vector <Player*> createComputerVector;

	//Create computers according to the input. Insert all computers into a vector
	for (int count = 0; count < numComputerInput; count++) {
		computerName = "Computer" + to_string(count+1);
		Player* pComputer = new Player(computerName); // create computer player
		createComputerVector.push_back(pComputer); // put the  computer into the vector
	}

	return createComputerVector;
}

/*
Function Name	= checkGameOver
Input(s)		= -
Output(s)		= -
Descriptions	=
Function for checking if the game condition for winning the game is met.
It checks whether the player with chips is only one or not.
*/
bool checkGameOver(vector <Player*> allPlayer, int numOfPlayer) {
	bool gameOverValue = true;
	int checkChips = 0;
	int playerWithChips = 0;
	
	//The loop will check how many player that has chips more than 0
	for (int counter = 0; counter < numOfPlayer; counter++) {
		checkChips = allPlayer[counter]->getChips();
		if (checkChips != 0){
			playerWithChips +=1; // Add one to the number of players with chips
		}
	}

	//If there is only 1 player with chips, it will end the game
	if (playerWithChips == 1){
		gameOverValue = false; // the value become false
	}

	return gameOverValue;
}

/*
Function Name	= dieAction
Input(s)		= -
Output(s)		= -
Descriptions	=
Function for giving an action to the chips of players towards the dice that has been rolled by the player who have the turn.
It will give different respond to each die if the die is L or C or R or O.
The function is for the game with normal effect.
So, it will give one chip to a player or pot (according to the die)
*/
void dieAction(vector <Player*> vPlayer,Player& pot, int pTurn, int numOfPlayer, char dieSide){
	
	//If the player gets die 'L'
	if (dieSide == 'L') {
		if (pTurn == 0) {
			cout << " Give one chip to " << vPlayer[numOfPlayer - 1]->getName() << endl;
			vPlayer[pTurn]->minusOneChips(); // Minus one chip for the current player
			vPlayer[numOfPlayer - 1]->plusOneChips(); // Plus one chip for the player in the left
		}
		else {
			cout << " Give one chip to " << vPlayer[pTurn - 1]->getName() << endl;
			vPlayer[pTurn]->minusOneChips();// Minus one chip for the current player
			vPlayer[pTurn - 1]->plusOneChips(); // Plus one chip for the player in the left
		}
	}

	//If the player gets die 'C'
	else if (dieSide == 'C') {
		cout << " Give one chip to " << pot.getName() << endl;
		vPlayer[pTurn]->minusOneChips(); // Minus one chip for the current player
		pot.plusOneChips(); // Plus one chip for the pot
	}

	//If the player gets die 'R'
	else if (dieSide == 'R') {
		if (pTurn == (numOfPlayer - 1)) {
			cout << " Give one chip to " << vPlayer[0]->getName() << endl;
			vPlayer[pTurn]->minusOneChips();// Minus one chip for the current player
			vPlayer[0]->plusOneChips(); // Plus one chip for the player in the right
		}
		else {
			cout << " Give one chip to " << vPlayer[pTurn + 1]->getName() << endl;
			vPlayer[pTurn]->minusOneChips();// Minus one chip for the current player
			vPlayer[pTurn + 1]->plusOneChips(); // Plus one chip for the player in the right
		}
	}

	//If the player gets die 'O'
	else if (dieSide == 'O') {
		cout << " Nothing happens. Keep your chips ..." << endl; //It will do nothing to the chips
	}

	//If the player gets die other than 'L', 'R', 'O'
	else {
		cout << " Error in die" << endl;
	}
}

/*
Function Name	= dieActionReverse
Input(s)		= -
Output(s)		= -
Descriptions	=
Function for giving an action to the chips of players towards the dice that has been rolled by the player who have the turn.
It will give different respond to each die if the die is L or C or R or O.
The function is for the game with reverse effect.
So, it will take one chip from a player or pot (according to the die)
*/
void dieActionReverse(vector <Player*> vPlayer, Player& pot, int pTurn, int numOfPlayer, char dieSide) {
	
	//If the player gets die 'L'
	if (dieSide == 'L') {


		// This is the code for doing nothing if the person on the left or right has 0 chips
		/*
		if (vPlayer[(pTurn + numOfPlayer - 1) % numOfPlayer]->getChips() <= 0) {
			cout << " Nothing happens. " << vPlayer[(pTurn + numOfPlayer - 1) % numOfPlayer]->getName() <<"'s chips is empty. " << endl;
		}
		else {
			cout << " Take one chip from " << vPlayer[(pTurn + numOfPlayer - 1) % numOfPlayer]->getName() << endl;
			vPlayer[pTurn]->plusChips();
			vPlayer[(pTurn + numOfPlayer - 1) % numOfPlayer]->minusChips();
		}
		*/

		int counter = 1;
		while (true) { // The loop is for finding someone that in the left but has chips more than 0
			if (vPlayer[(pTurn + counter) % numOfPlayer]->getChips() == 0) {
				counter++;
				if ((pTurn + counter) % numOfPlayer == pTurn) {
					cout << "No one has chips to take from, you are the winner" << endl;
					break;
				}
				continue;
			}
			else {
				vPlayer[(pTurn + counter) % numOfPlayer]->minusOneChips(); //Minus one chips for the player in the left
				vPlayer[pTurn]->plusOneChips(); //Plus one chips to the current player
				cout << " Take one chip from " << vPlayer[(pTurn + counter) % numOfPlayer]->getName() << endl; 
				break;
			}
		}
		
	}

	//If the player gets die 'C'
	else if (dieSide == 'C') {
		if (pot.getChips() == 0) {
			cout << " Nothing happens. The "<<pot.getName()<<" is empty. " << endl; // i will do nothing if the pot is empty
		}
		else {
			cout << " Take one chip from " << pot.getName() << endl;
			vPlayer[pTurn]->plusOneChips(); //Plus one chips to the current player
			pot.minusOneChips(); //Minus one chips for pot
		}
	}

	//If the player gets die 'R'
	else if (dieSide == 'R') {

		// This is the code for doing nothing if the person on the left or right has 0 chips
		/*
		if (vPlayer[(pTurn + 1) % numOfPlayer]->getChips() <= 0) {
			cout << " Nothing happens. " << vPlayer[(pTurn + 1) % numOfPlayer]->getName() << "'s chips is empty. " << endl;
		}
		else {
			vPlayer[(pTurn + 1) % numOfPlayer]->minusChips();
			cout << " Take one chip from " << vPlayer[(pTurn + 1) % numOfPlayer]->getName() << endl;
			vPlayer[pTurn]->plusChips();
			vPlayer[(pTurn + 1) % numOfPlayer]->minusChips();
		}
		*/ 
				
		int counter = 1;
		while (true) { // The loop is for finding someone that in the left but has chips more than 0
			if (vPlayer[(pTurn+counter)%numOfPlayer]->getChips() == 0) {
				counter++;
				if ((pTurn + numOfPlayer - counter) % numOfPlayer == pTurn) {
					cout << "No one has chips to take from, you are the winner" << endl;
					break;
				}
				continue;
			}
			else {
				vPlayer[(pTurn + counter) % numOfPlayer]->minusOneChips(); //Minus one chips for the player in the right
				vPlayer[pTurn]->plusOneChips();//Plus one chips to the current player
				cout << " Take one chip from " << vPlayer[(pTurn + counter) % numOfPlayer]->getName() << endl;
				break;
			}
		}
	}

	//If the player gets die 'O'
	else if (dieSide == 'O') {
		cout << " Nothing happens. Keep your chips ..." << endl; //It will do nothing to the chips
	}

	//If the player gets die other than 'L', 'R', 'O'
	else {
		cout << " Error in die" << endl;
	}
}
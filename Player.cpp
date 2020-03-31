#include "Player.h"

Player::Player(string newPlayerName) {
	playerName = newPlayerName;
}

Player::~Player() {

}

string Player::getName() {
	return playerName;
}

void Player::setChips(int numberOfChips) {
	playerChips = numberOfChips;
}

int Player::getChips() {
	return playerChips;
}

void Player::minusOneChips() {
	playerChips--;
}

void Player::plusOneChips() {
	playerChips++;
}

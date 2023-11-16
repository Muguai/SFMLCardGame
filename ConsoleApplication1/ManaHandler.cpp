#include "Header/ManaHandler.hpp"
#include <iostream>

/*	ManaHander() [Constructor]
	Takes in the start mana and sets the current mana as well as the max mana.
	param increaseFactor: How many mana points per turn max mana should increase.
	param maxPossibleMana: How much mana is theoretically possible. 
*/

ManaHandler::ManaHandler(int startMana, int increaseFactor, int maxPossibleMana){
	mana = startMana;
	manaCurrentMax = startMana;
	manaIncrease = increaseFactor;
	manaGlobalMax = maxPossibleMana;
}

/*	tryPlaceMonster()
	A function that takes in the cost and subtracts the cost if possible and returns true,
	else returns false. The return value should be used to see if it is possible to place
	a monster on the board.
*/

bool ManaHandler::tryPlaceMonster(int cost){
	if (cost <= mana) {
		mana -= cost;
		return true;
	}
	return false;
}

/*	getMana()
	Simple getter.
	return: Current mana
*/

int ManaHandler::getMana() {
	return this->mana;
}


/*	restoreMana()
	Restores mana to the current max. 
	Should be called in a public function that deals with updates per turn.
*/

void ManaHandler::restoreMana() {
	mana = manaCurrentMax;
}

/*	incrementMaxMana()
	Increases the currentMaxMana with the amount specified in manaIncrease.
	The current max mana will not exceed the theoretical limit.
*/

void ManaHandler::incrementMaxMana() {
	int min = manaCurrentMax + manaIncrease;
	if (min > manaGlobalMax) {
		min = manaGlobalMax;
	}
	manaCurrentMax = min;
}

void ManaHandler::update(float deltaTime, sf::RenderWindow& window) {
}
void ManaHandler::initialize() {
}
#include "Header/ManaHandler.hpp"
#include <iostream>

/*	ManaHander() [Constructor]
	Takes in the start mana and sets the current mana as well as the max mana.
	param increaseFactor: How many mana points per turn max mana should increase.
	param maxPossibleMana: How much max mana is theoretically possible. 
*/

ManaHandler::ManaHandler(bool player, int startMana, int increaseFactor, int maxPossibleMana){
	this->player = player;
	mana = startMana;
	manaCurrentMax = startMana;
	manaIncrease = increaseFactor;
	manaGlobalMax = maxPossibleMana;


	if (!font.loadFromFile("Fonts/COMIC.ttf")) {
		cout << "Error loading font!";
	}
}

// Default Constructor: 
ManaHandler::ManaHandler() {}

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

/*	setPosition()
	Simple setter.
*/

void ManaHandler::setPosition(sf::Vector2f pos) {
	x = pos.x;
	y = pos.y;
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

/*	draw()
*	Renders the mana of the player who the mana handler belongs to.
*/

void ManaHandler::draw(sf::RenderWindow& window) {
	float radius = 30.0f;
	sf::Text manaText(to_string(mana), font, 18);
	manaText.setPosition(x + radius/2, y+radius/2);

	manaIcon.setRadius(radius);
	manaIcon.setPosition(x, y);
	manaIcon.setFillColor(sf::Color::Blue);

	window.draw(manaIcon);
	window.draw(manaText);
}

/*	update()
*	1. Sets up coordinates based on screen size.
*	2. Re-renders the ManaHandler object.
*/

void ManaHandler::update(float deltaTime, sf::RenderWindow& window) {
	float xOffset = 100;
	float yOffset = 100;
	if (player) {
		x = window.getSize().x - xOffset;
		y = window.getSize().y - yOffset;
	}
	else {
		x = xOffset;
		y = yOffset;
	}
	draw(window);
}
void ManaHandler::initialize() {
}
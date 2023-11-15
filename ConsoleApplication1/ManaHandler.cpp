#include "Header/ManaHandler.hpp"
#include <iostream>

ManaHandler::ManaHandler(int startMana, int increaseFactor){
	mana = startMana;
	manaIncrease = increaseFactor;
}

bool ManaHandler::sufficientMana(int cost){
	return cost <= mana;
}

int ManaHandler::getMana() {
	return this->mana;
}

void ManaHandler::update(float deltaTime, sf::RenderWindow& window) {
}

void ManaHandler::initialize() {
}
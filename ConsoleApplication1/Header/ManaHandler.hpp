#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GameObject.hpp>
#include <GameObjectManager.hpp>

using namespace std;
class ManaHandler : public GameObject {
public:
	ManaHandler(int startMana, int increaseFactor, int maxPossibleMana);
	int getMana();
	bool tryPlaceMonster(int manaCost);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;

private:
	void restoreMana();
	void incrementMaxMana();
	int mana;
	int manaCurrentMax;
	int manaIncrease;
	int manaGlobalMax;
};
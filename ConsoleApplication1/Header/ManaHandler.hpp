#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GameObject.hpp>
#include <GameObjectManager.hpp>

using namespace std;
class ManaHandler : public GameObject {
public:
	ManaHandler(int x, int y, int startMana, int increaseFactor, int maxPossibleMana);
	int getMana();
	bool tryPlaceMonster(int manaCost);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;

private:
	sf::Font font;
	sf::CircleShape manaIcon;
	int x;
	int y;

	void restoreMana();
	void incrementMaxMana();
	int mana;
	int manaCurrentMax;
	int manaIncrease;
	int manaGlobalMax;
};
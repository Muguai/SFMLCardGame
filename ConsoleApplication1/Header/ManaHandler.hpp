#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GameObject.hpp>
#include <GameObjectManager.hpp>

using namespace std;
class ManaHandler : public GameObject {
public:
	ManaHandler();
	ManaHandler(bool player, int startMana, int increaseFactor, int maxPossibleMana);
	int getMana();
	bool tryPlaceMonster(int manaCost);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;
	void setPosition(sf::Vector2f pos);

private:
	sf::Font font;
	sf::CircleShape manaIcon;
	bool player;

	int x;
	int y;
	void restoreMana();
	void incrementMaxMana();
	int mana;
	int manaCurrentMax;
	int manaIncrease;
	int manaGlobalMax;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GameObject.hpp>
#include <GameObjectManager.hpp>

using namespace std;
class ManaHandler : public GameObject {
public:
	ManaHandler(int startMana, int increaseFactor);
	int getMana();
	bool sufficientMana(int manaCost);
	void update(float deltaTime, sf::RenderWindow& window) override;
	void initialize() override;

private:
	int mana;
	int manaIncrease;
};
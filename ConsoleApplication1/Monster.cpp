#include <Header/Monster.hpp>
#include <SFML/Graphics.hpp>

Monster::Monster(int atk, int hp, string n, int s) {
	attack = atk;
	health = hp;
	name = n;
	slot = s;
}

void Monster::drawMonster(sf::Vector2f pos, float radius, sf::RenderWindow& window) {
	// Render image of the monster:
	sf::CircleShape outerCircle;
	outerCircle.setPosition(pos);
	outerCircle.setRadius(radius);
	outerCircle.setFillColor(sf::Color::Blue);
	window.draw(outerCircle);
	
	// Data for the orbs containing Health / Attack damage numbers:
	float orbMargin = 15.0f;
	float orbRadius = 15.0f;
	float orbOffset = radius - orbRadius;

	// Render Remaining Health:
	sf::CircleShape redCircle;
	sf::Vector2f redPos(orbOffset + pos.x + sqrt((radius*radius) / 2) - orbMargin, orbOffset + pos.y + sqrt((radius*radius) / 2) - orbMargin);
	redCircle.setPosition(redPos);
	redCircle.setRadius(orbRadius);
	redCircle.setFillColor(sf::Color::Red);
	window.draw(redCircle);
	
	// Render Attack Damage:
	sf::CircleShape yellowCircle;
	sf::Vector2f yellowPos(orbOffset + pos.x + -sqrt((radius * radius) / 2) + orbMargin, orbOffset + pos.y + sqrt((radius * radius) / 2) - orbMargin);
	yellowCircle.setPosition(yellowPos);
	yellowCircle.setRadius(orbRadius);
	yellowCircle.setFillColor(sf::Color::Yellow);
	window.draw(yellowCircle);
}
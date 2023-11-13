#include <Header/Monster.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

Monster::Monster(){
	null = true;
}

Monster::Monster(int atk, int hp, string n, int s) {
	attack = atk;
	health = hp;
	name = n;
	slot = s;
	null = false;

	if (!monsterTexture.loadFromFile("Images/" + name + ".png")) {
		cout << "Error loading card image!";
	}
	if (!font.loadFromFile("Fonts/COMIC.ttf")) {
		cout << "Error loading font!";
	}
}


void Monster::update(float deltaTime, sf::RenderWindow& window) {
}

void Monster::initialize() {
}

bool Monster::isNull() {
	return null;
}

void Monster::drawMonster(sf::Vector2f pos, float radius, sf::RenderWindow& window) {
	// Render the bounding circle:
	sf::CircleShape outerCircle;
	outerCircle.setPosition(pos);
	outerCircle.setRadius(radius);
	outerCircle.setFillColor(sf::Color::White);
	outerCircle.setOutlineThickness(4.f);
	outerCircle.setOutlineColor(sf::Color::Blue);
	window.draw(outerCircle);
	
	// Monster Portrait:
	sf::CircleShape portrait;
	float portraitRadius = 60.0f;
	float portraitOffset = radius - portraitRadius;
	sf::Vector2f portraitPos(pos.x + portraitOffset, pos.y + portraitOffset);
	portrait.setPosition(portraitPos);
	portrait.setRadius(portraitRadius);
	portrait.setTexture(&monsterTexture);
	window.draw(portrait);

	// Data for the orbs containing Health / Attack damage numbers:
	float orbMargin = 0.0f;
	float orbRadius = 15.0f;
	float orbOffset = radius - orbRadius;

	// Render Remaining Health:
	sf::CircleShape redCircle;
	sf::Vector2f redPos(orbOffset + pos.x + sqrt((radius*radius) / 2) - orbMargin, orbOffset + pos.y + sqrt((radius*radius) / 2) - orbMargin);
	redCircle.setPosition(redPos);
	redCircle.setRadius(orbRadius);
	redCircle.setFillColor(sf::Color::Red);
	redCircle.setOutlineThickness(2.f);
	redCircle.setOutlineColor(sf::Color::Blue);
	window.draw(redCircle);
	
	// Text within the Red Orb:
	sf::Text redText(to_string(health), font, 14);
	redText.setFillColor(sf::Color::Black);
	redText.setPosition(sf::Vector2f(redPos.x + orbRadius/2, redPos.y+orbRadius/2));
	window.draw(redText);
	
	// Render Yellow Orb (Attack):
	sf::CircleShape yellowCircle;
	sf::Vector2f yellowPos(orbOffset + pos.x + -sqrt((radius * radius) / 2) + orbMargin, orbOffset + pos.y + sqrt((radius * radius) / 2) - orbMargin);
	yellowCircle.setPosition(yellowPos);
	yellowCircle.setRadius(orbRadius);
	yellowCircle.setFillColor(sf::Color::Yellow);
	yellowCircle.setOutlineThickness(2.f);
	yellowCircle.setOutlineColor(sf::Color::Blue);
	window.draw(yellowCircle);

	// Text within yellow Orb:
	sf::Text yellowText(to_string(attack), font, 14);
	yellowText.setFillColor(sf::Color::Black);
	yellowText.setPosition(sf::Vector2f(yellowPos.x + orbRadius / 2, yellowPos.y + orbRadius / 2));
	window.draw(yellowText);
}
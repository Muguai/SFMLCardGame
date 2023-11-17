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
	clickLock = true;
	clicked = false;
	borderColor = sf::Color::Blue;

	if (!monsterTexture.loadFromFile("Images/" + name + ".png")) {
		cout << "Error loading card image!";
	}
	if (!font.loadFromFile("Fonts/COMIC.ttf")) {
		cout << "Error loading font!";
	}
}

void Monster::takeDamage(int dmg) {
	health -= dmg;
}

void Monster::update(float deltaTime, sf::RenderWindow& window) {
	checkClicked(window);
}

void Monster::initialize() {
}

bool Monster::isNull() {
	return null;
}


bool Monster::getClicked() {
	return clicked;
}

int Monster::getAttack() {
	return attack;
}


int Monster::getHealth(){
	return attack;
}


void Monster::unclick() {
	clicked = false;
}

/*	checkClicked()
	A function that checks if the current monster is clicked and if so alternate
	the boolean value corresponding to the clicked property. clickLock is used to
	lock the click in place, i.e, to make it a unique occurance and to prevent
	holding in mouse 1 from triggering multiple "clicks".
*/

void Monster::checkClicked(const sf::RenderWindow& window) {
	if (clicked) {
		borderColor = sf::Color::Red;
	}
	else {
		borderColor = sf::Color::Blue;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHovered(window)) {
		if (!clickLock) {
			clickLock = true;
			clicked = !clicked;
		}
	}
	else {
		clickLock = false;
	}

	
}

bool Monster::isHovered(const sf::RenderWindow& window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::FloatRect cardBounds = outerCircle.getGlobalBounds();
	return cardBounds.contains(static_cast<sf::Vector2f>(mousePosition));
}

void Monster::drawMonster(sf::Vector2f pos, float radius, sf::RenderWindow& window) {
	// 1. Render the bounding circle:
	outerCircle.setPosition(pos);
	outerCircle.setRadius(radius);
	outerCircle.setFillColor(sf::Color::White);
	outerCircle.setOutlineThickness(4.f);
	outerCircle.setOutlineColor(borderColor);
	window.draw(outerCircle);
	
	// 2. Monster Portrait:
	sf::CircleShape portrait;
	float portraitRadius = 60.0f;
	float portraitOffset = radius - portraitRadius;
	sf::Vector2f portraitPos(pos.x + portraitOffset, pos.y + portraitOffset);
	portrait.setPosition(portraitPos);
	portrait.setRadius(portraitRadius);
	portrait.setTexture(&monsterTexture);
	window.draw(portrait);

	// 3. Data for the orbs containing Health / Attack damage numbers:
	float orbMargin = 0.0f;
	float orbRadius = 15.0f;
	float orbOffset = radius - orbRadius;

	// 4. Render Remaining Health:
	sf::CircleShape redCircle;
	sf::Vector2f redPos(orbOffset + pos.x + sqrt((radius*radius) / 2) - orbMargin, orbOffset + pos.y + sqrt((radius*radius) / 2) - orbMargin);
	redCircle.setPosition(redPos);
	redCircle.setRadius(orbRadius);
	redCircle.setFillColor(sf::Color::Red);
	redCircle.setOutlineThickness(2.f);
	redCircle.setOutlineColor(borderColor);
	window.draw(redCircle);
	
	// 5. Text within the Red Orb:
	sf::Text redText(to_string(health), font, 14);
	redText.setFillColor(sf::Color::Black);
	redText.setPosition(sf::Vector2f(redPos.x + orbRadius/2, redPos.y+orbRadius/2));
	window.draw(redText);
	
	// 6. Render Yellow Orb (Attack):
	sf::CircleShape yellowCircle;
	sf::Vector2f yellowPos(orbOffset + pos.x + -sqrt((radius * radius) / 2) + orbMargin, orbOffset + pos.y + sqrt((radius * radius) / 2) - orbMargin);
	yellowCircle.setPosition(yellowPos);
	yellowCircle.setRadius(orbRadius);
	yellowCircle.setFillColor(sf::Color::Yellow);
	yellowCircle.setOutlineThickness(2.f);
	yellowCircle.setOutlineColor(borderColor);
	window.draw(yellowCircle);

	// 7. Text within yellow Orb:
	sf::Text yellowText(to_string(attack), font, 14);
	yellowText.setFillColor(sf::Color::Black);
	yellowText.setPosition(sf::Vector2f(yellowPos.x + orbRadius / 2, yellowPos.y + orbRadius / 2));
	window.draw(yellowText);
}
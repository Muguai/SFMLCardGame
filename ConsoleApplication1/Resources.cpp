#include <Card.hpp>
#include <iostream>
#include <deque>
using namespace std;

deque<Card> addQuantity(deque<Card> cardStack, int n, int atk, int hp, sf::Vector2f size, string name, std::function<void()> f) {
	for (int i = 0; i < n; i++) {
		Card card(atk, hp, size, name, f);
		cardStack.push_back(card);
	}

	return cardStack;
}

deque<Card> getInitCards() {
	deque<Card> cardStack;
	sf::Vector2f cardSize = sf::Vector2f(150.f, 200.f);
	auto emptyFunction = [](){};

	// Calls to add cards to the "superdeck":
	cardStack = addQuantity(cardStack, 10, 10, 10, cardSize, "Troll", emptyFunction);
	cardStack = addQuantity(cardStack, 5, 100, 100, cardSize, "Dragon", emptyFunction);
	cardStack = addQuantity(cardStack, 3, 100, 100, cardSize, "Dragon Lord", emptyFunction);

	return cardStack;
}
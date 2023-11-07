#include <Card.hpp>
#include <iostream>
#include <deque>
using namespace std;

/*	addQuantity
	A function that adds a quantity of n cards with specified spec to a cardstack.
	return: The updated deck.
*/

deque<Card> addQuantity(deque<Card> cardStack, int n, int atk, int hp, sf::Vector2f size, string name, std::function<void()> f) {
	for (int i = 0; i < n; i++) {
		Card card(atk, hp, size, name, f);
		cardStack.push_back(card);
	}

	return cardStack;
}

/*	getChaosSuperDeck()
	getChaosSuperDeck() is a function that returns the deck containing every card.
	1. Init the cardStack and set properties, like size, functions etc.
	2. Add  quantities of (Chaos faction) cards with ATK/HP etc, added together into a super deck:
	3. Return the super deck.
*/ 

deque<Card> getChaosSuperDeck() {
	deque<Card> superDeck;
	sf::Vector2f cardSize = sf::Vector2f(150.f, 200.f);
	auto emptyFunction = [](){};
	
	superDeck = addQuantity(superDeck, 10, 10, 10, cardSize, "Troll", emptyFunction);
	superDeck = addQuantity(superDeck, 3, 100, 100, cardSize, "Dragon", emptyFunction);
	superDeck = addQuantity(superDeck, 1, 1000, 1000, cardSize, "Dragon Lord", emptyFunction);

	return superDeck;
}
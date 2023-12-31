#include <Card.hpp>
#include <iostream>
#include <deque>
#include <Header/Resources.hpp>
#include "AllCardsManager.hpp"
class AllCardsManager;


using namespace std;
sf::Vector2f cardSize = sf::Vector2f(150.f, 200.f);
auto emptyFunction = []() {};

/*	addQuantity
	A function that adds a quantity of n cards with specified spec to a cardstack.
	return: The updated deck.
*/

deque<Card> addQuantity(deque<Card> cardStack, int n, int atk, int hp, int cost, sf::Vector2f size, string name, std::function<void()> f) {
	Card cardtomap(atk, hp, cost, size, name, f);

	for (int i = 0; i < n; i++) {
		Card card(atk, hp, cost, size, name, f);
		cardStack.push_back(card);
	}


	return cardStack;
}

/*	getChaosSuperDeck()
	getChaosSuperDeck() is a function that returns the deck containing every card for the chaos faction.
	1. Init the cardStack and set properties, like size, functions etc.
	2. Add  quantities of (Chaos faction) cards with ATK/HP etc, added together into a super deck:
	3. Return the super deck.
*/ 

deque<Card> getChaosSuperDeck() {
	deque<Card> superDeck;
	
	superDeck = addQuantity(superDeck, 10, 10,  10,    1, cardSize, "Troll", emptyFunction);
	superDeck = addQuantity(superDeck, 3, 100,  100,   3, cardSize, "Dragon", emptyFunction);
	superDeck = addQuantity(superDeck, 2, 200,  200,   5, cardSize, "Ogre Magi", emptyFunction);
	superDeck = addQuantity(superDeck, 1, 1000, 1000,  10, cardSize, "Dragon Lord", emptyFunction);

	return superDeck;
}

/*	getLifeSuperDeck()
	getLifeSuperDeck() is a function that returns the superdeck containing every card of the life fac.
	1. Init the cardStack and set properties, like size, functions etc.
	2. Add  quantities of (Chaos faction) cards with ATK/HP etc, added together into a super deck:
	3. Return the super deck.
*/

deque<Card> getLifeSuperDeck() {
	deque<Card> superDeck;

	superDeck = addQuantity(superDeck, 10, 10, 10, 1, cardSize, "Chubby Wubby Angel", emptyFunction);
	superDeck = addQuantity(superDeck, 10, 10, 10, 1, cardSize, "Soprano Bud", emptyFunction);


	return superDeck;
}
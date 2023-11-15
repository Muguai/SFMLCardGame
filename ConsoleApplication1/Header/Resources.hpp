#pragma once
#include <SFML/Graphics.hpp>
deque<Card> getChaosSuperDeck();
deque<Card> getLifeSuperDeck();
deque<Card> addQuantity(deque<Card> cardStack, int n, int atk, int hp, int cost, sf::Vector2f size, string name, std::function<void()> f);

#include <SFML/Graphics.hpp>

class VectorHelper {
public:
    static sf::Vector2f normalize(const sf::Vector2f& vector);
    static float distanceTo(const sf::Vector2f& from, const sf::Vector2f& to);
};

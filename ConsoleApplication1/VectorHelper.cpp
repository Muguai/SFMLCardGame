#include "VectorHelper.hpp"
#include <cmath>

sf::Vector2f VectorHelper::normalize(const sf::Vector2f& vector) {
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (magnitude != 0) {
        return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);
    }
    return vector;
}


float VectorHelper::distanceTo(const sf::Vector2f& from, const sf::Vector2f& to) {
    float dx = to.x - from.x;
    float dy = to.y - from.y;
    return std::sqrt(dx * dx + dy * dy);
}
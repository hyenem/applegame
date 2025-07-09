
#include "Apple.hpp"

Apple::Apple(float x, float y, int val) : value(val) {
    shape = sf::CircleShape(20);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
}

bool Apple::contains(sf::Vector2f point) {
    return shape.getGlobalBounds().contains(point);
}

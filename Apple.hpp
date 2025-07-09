
#ifndef APPLE_HPP
#define APPLE_HPP
#include <SFML/Graphics.hpp>

class Apple {
public:
    sf::CircleShape shape;
    int value;

    Apple(float x, float y, int val);
    bool contains(sf::Vector2f point);
};

#endif

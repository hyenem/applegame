
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Apple.hpp"

class Game {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text scoreText;
    sf::Clock clock;
    int score;
    std::vector<Apple> apples;

    void processEvents();
    void update(sf::Time dt);
    void render();
    void handleInput();
    void generateApples();

public:
    Game(sf::RenderWindow& win);
    void run();
};

#endif

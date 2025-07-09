
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Apple Game");
    Game game(window);
    game.run();
    return 0;
}

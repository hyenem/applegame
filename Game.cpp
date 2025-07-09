
#include "Game.hpp"
#include <sstream>
#include <cstdlib>

Game::Game(sf::RenderWindow& win) : window(win), score(0) {
    font.loadFromFile("Assets/font.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    generateApples();
}

void Game::run() {
    sf::Time dt;
    while (window.isOpen()) {
        processEvents();
        dt = clock.restart();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    handleInput();
}

void Game::update(sf::Time dt) {
    std::stringstream ss;
    ss << "Score: " << score;
    scoreText.setString(ss.str());
}

void Game::render() {
    window.clear();
    for (auto& apple : apples)
        window.draw(apple.shape);
    window.draw(scoreText);
    window.display();
}

void Game::handleInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        for (auto it = apples.begin(); it != apples.end();) {
            if (it->contains(mousePos)) {
                score += it->value;
                it = apples.erase(it);
            } else ++it;
        }
    }
}

void Game::generateApples() {
    for (int i = 0; i < 5; ++i) {
        float x = static_cast<float>(rand() % 700 + 50);
        float y = static_cast<float>(rand() % 500 + 50);
        int val = rand() % 10 + 1;
        apples.emplace_back(x, y, val);
    }
}

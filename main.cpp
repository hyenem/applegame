#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <optional>
#include <algorithm>
#include <string>
#include <random>
#include <vector>
#include <windows.h>
#include <SFML/Audio.hpp>


using namespace sf;
using std::vector;

float radius = 20.f;
float offsetX = 50.f;
float offsetY = 50.f;
float spacingX = 60.f;
float spacingY = 60.f;

class Fruit {
public:
    int type;
    int number;
    CircleShape shape;

    std::string toString() {
        return std::to_string(type) + " " + std::to_string(number);
    }
};

void colorFruit(Fruit& f){
    if(f.type == 1){
        f.shape.setFillColor(Color::Red);
    } else {
        f.shape.setFillColor(Color::Magenta);
    }
}
void fill_board(std::vector<std::vector<Fruit>>& board, double ratio = 0.2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> type_dist(0, 1);
    std::uniform_int_distribution<int> number_dist(1, 9);

    int rows = board.size();
    int cols = board[0].size();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Fruit& f = board[row][col];
            f.type = 1 + (int)(type_dist(gen) <= ratio);
            f.number = number_dist(gen);
            f.shape = CircleShape(radius);
            colorFruit(f);
            board[row][col].shape.setOrigin(Vector2f(radius, radius));
            board[row][col].shape.setPosition(Vector2f(
                offsetX + col * spacingX,
                offsetY + row * spacingY + 70
            ));
        }
    }
}

int fruit_pop(vector<vector<Fruit>>& board, int s_row, int s_col, int e_row, int e_col) {
    int score = 0;
    int num_sum = 0;
    int min_type = 2;
    for (int row = s_row; row <= e_row && num_sum <= 10; ++row) {
        for (int col = s_col; col <= e_col && num_sum <= 10; ++col) {
            num_sum += board[row][col].number;
            if (board[row][col].type) {
                score++;
                if (board[row][col].type < min_type) {
                    min_type = board[row][col].type;
                }
            }
        }
    }

    if (num_sum == 10) {
        for (int row = s_row; row <= e_row && num_sum <= 10; ++row) {
            for (int col = s_col; col <= e_col && num_sum <= 10; ++col) {
                board[row][col].type = 0;
                board[row][col].number = 0;
            }
        }
        return score * min_type;
    } else {
        return 0;
    }
}


int main() {
    RenderWindow window(VideoMode({ 1200u, 800u }), "Fruit Board - SFML 3.0");
    window.setFramerateLimit(60);

    Font font;
    if (!font.openFromFile("Roboto-VariableFont_wdth,wght.ttf")) {
        std::cerr << "폰트 로드 실패!\n";
        return -1;
    }

    

    int rows = 17;
    int cols = 10;
    double lemonRatio = 0.33;

    int minx = cols + 1, miny = rows + 1, maxx = -1, maxy = -1;
    sf::Music music;

    if (!music.openFromFile("apple_bgm.wav")){
        return -1;
    }

    music.play();
    music.setLooping(true);

    int score = -1;
    Clock gameTimer;
    float timeLimit = 60.;

    vector<vector<Fruit>> board(cols, vector<Fruit>(rows));

    bool selecting = false;
    Vector2f startPos;
    RectangleShape selectionBox;
    selectionBox.setFillColor(Color(0, 0, 255, 50));
    selectionBox.setOutlineColor(Color::Blue);
    selectionBox.setOutlineThickness(1);

    bool gameStarted = false;

    RectangleShape startButton(Vector2f(200.f, 60.f));
    startButton.setFillColor(Color::Green);
    startButton.setPosition(Vector2f(950.f, 700.f));

    Text startText(font);
    startText.setCharacterSize(24);
    startText.setFillColor(Color::White);

    Text scoreText(font);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(Vector2f(700.f, 10.f));


    Text timerText(font);
    timerText.setCharacterSize(28);
    timerText.setFillColor(Color::Red);
    timerText.setPosition(Vector2f(950.f, 10.f)); // 오른쪽 위 위치

    while (window.isOpen()) {
        while (const std::optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePress = event->getIf<Event::MouseButtonPressed>()) {
                if (mousePress->button == Mouse::Button::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (startButton.getGlobalBounds().contains(mousePos)) {
                        if (!gameStarted) {
                            gameStarted = true;
                            gameTimer.restart();
                            score = 0;
                            fill_board(board, lemonRatio);
                        } else {
                            gameStarted = false;
                            score = 0;
                            gameTimer.restart();
                            fill_board(board, lemonRatio);
                        }
                    } else if (gameStarted) {
                        selecting = true;
                        startPos = mousePos;
                        selectionBox.setPosition(startPos);
                        selectionBox.setSize(Vector2f(0, 0));
                    }
                }
            }

            if (const auto* mouseRelease = event->getIf<Event::MouseButtonReleased>()) {
                if (mouseRelease->button == Mouse::Button::Left) {
                    selecting = false;
                    if (gameStarted) {
                        score += fruit_pop(board, minx, miny, maxx, maxy);
                        minx = 11, miny = 18, maxx = -1, maxy = -1;
                        for (int i = 0; i < 10; i++) {
                            for (int j = 0; j < 17; j++) {
                                Fruit& f = board[i][j];
                                colorFruit(f);
                            }
                        }
                    }
                }
            }
        }

        if (selecting && gameStarted) {
            Vector2f currentPos = window.mapPixelToCoords(Mouse::getPosition(window));
            Vector2f size(currentPos - startPos);
            selectionBox.setSize(size);

            FloatRect selectionBounds(selectionBox.getGlobalBounds());
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 17; j++) {
                    Fruit& f = board[i][j];
                    FloatRect fruitBounds = f.shape.getGlobalBounds();
                    if (auto inter = selectionBounds.findIntersection(fruitBounds)) {
                        f.shape.setFillColor(Color::Yellow);
                        minx = std::min(minx, i);
                        miny = std::min(miny, j);
                        maxx = std::max(maxx, i);
                        maxy = std::max(maxy, j);
                    } else {
                        colorFruit(f);
                    }
                }
            }
        }
        float gameTimeRemain = timeLimit - gameTimer.getElapsedTime().asSeconds();
        if (gameTimeRemain < 0){
            gameStarted = false;
            selecting = false;
            gameTimer.stop();
        }
        timerText.setString("Time: " + std::to_string((int) gameTimeRemain));
        scoreText.setString("Score: " + std::to_string(score));

        startText.setString(gameStarted ? "END" : "START");
        auto textBounds = startText.getLocalBounds();
        startText.setOrigin(textBounds.position + textBounds.size / 2.f);
        startText.setPosition(Vector2f(
            startButton.getPosition().x + startButton.getSize().x / 2.f,
            startButton.getPosition().y + startButton.getSize().y / 2.f
        ));

        window.clear(Color::White);

        if (gameStarted) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 17; j++) {
                    Fruit& f = board[i][j];
                    if (f.number != 0) {
                        window.draw(f.shape);

                        Text text(font);
                        text.setString(std::to_string(f.number));
                        text.setCharacterSize(22);
                        text.setFillColor(Color::White);

                        auto bounds = text.getLocalBounds();
                        text.setOrigin(bounds.position + bounds.size / 2.f);
                        text.setPosition(f.shape.getPosition());

                        window.draw(text);
                    }
                }
            }

            window.draw(scoreText);
            window.draw(timerText);
        }

        if (selecting && gameStarted) {
            window.draw(selectionBox);
        }

        window.draw(startButton);
        window.draw(startText);

        if(!gameStarted){
            Text resultText(font);
            resultText.setCharacterSize(28);
            resultText.setFillColor(Color::Black);
            resultText.setPosition(Vector2f(400.f, 350.f));
            if(score==-1){
                resultText.setString("Let's Start");
            } else {
                resultText.setString("Result : " + std::to_string(score));
            }
            window.draw(resultText);
        }

        window.display();
    }

    return 0;
}

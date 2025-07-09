#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <algorithm>
#include <string>
#include <random>
#include <vector>
#include <windows.h>

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

void fill_board(std::vector<std::vector<Fruit>>& board, double ratio = 0.2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> type_dist(0, 1);
    std::uniform_int_distribution<int> number_dist(1, 9);

    int cols = board.size();
    int rows = board[0].size();

    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            board[col][row].type = 1 + (int) (type_dist(gen) <= ratio);
            board[col][row].number = number_dist(gen);
            board[col][row].shape = CircleShape(radius);
            board[col][row].shape.setFillColor(Color::Red);
            board[col][row].shape.setOrigin(Vector2f(radius, radius));
            board[col][row].shape.setPosition(Vector2f(
                offsetX + row * spacingX,
                offsetY + col * spacingY
            ));
        }
    }
}

int fruit_pop(vector<vector<Fruit>>& board, int s_col, int s_row, int e_col, int e_row){
    std:: cout<< s_col <<", " << s_row <<", " << e_col <<", " << e_row << std::endl;
    int score = 0;
    int num_sum = 0;
    int min_type = 2;
    for (int col = s_col; col <= e_col && num_sum <= 10; ++col) {
        for (int row = s_row; row <= e_row && num_sum <= 10; ++row) {
            num_sum += board[col][row].number;
            if(board[col][row].type){
                score++;
                if (board[col][row].type < min_type){
                    min_type = board[col][row].type;
                }
            }
        }
    }

    if(num_sum == 10){
        for (int col = s_col; col <= e_col && num_sum <= 10; ++col) {
            for (int row = s_row; row <= e_row && num_sum <= 10; ++row) {
                board[col][row].type = 0;
                board[col][row].number = 0;
            }
        }
        return score * min_type;
    } else {
        return 0;
    }
}

int main() {
    RenderWindow window(VideoMode({1200u, 800u}), "Fruit Board - SFML 3.0");
    window.setFramerateLimit(60);

    Font font;
    if (!font.openFromFile("Roboto-VariableFont_wdth,wght.ttf")) {
        std::cerr << "폰트 로드 실패!\n";
        return -1;
    }


    int minx=11, miny=18, maxx=-1, maxy=-1;

    int rows = 17;
    int cols = 10;
    double lemon_ratio = 0.5;

    int score = 0;

    vector<vector<Fruit>> board(cols, vector<Fruit>(rows));

    fill_board(board, lemon_ratio);


    bool selecting = false;
    Vector2f startPos;
    RectangleShape selectionBox;
    selectionBox.setFillColor(Color(0, 0, 255, 50));
    selectionBox.setOutlineColor(Color::Blue);
    selectionBox.setOutlineThickness(1);

    while (window.isOpen()) {
        while (const std::optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePress = event->getIf<Event::MouseButtonPressed>()) {
                if (mousePress->button == Mouse::Button::Left) {
                    selecting = true;
                    startPos = window.mapPixelToCoords(Mouse::getPosition(window));
                    selectionBox.setPosition(startPos);
                    selectionBox.setSize(Vector2f(0, 0));
                }
            }

            if (const auto* mouseRelease = event->getIf<Event::MouseButtonReleased>()) {
                if (mouseRelease->button == Mouse::Button::Left) {
                    selecting = false;
                    fruit_pop(board, minx, miny, maxx, maxy);
                    minx=11, miny=18, maxx=-1, maxy=-1;
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 17; j++) {
                            Fruit& f = board[i][j];
                            f.shape.setFillColor(Color::Red);
                        }
                    }
                }
            }
        }

        if (selecting) {
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
                        f.shape.setFillColor(Color::Red);
                    }
                }
            }
        }

        window.clear(Color::White);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 17; j++) {
                Fruit& f = board[i][j];
                if(f.number!=0){
                    window.draw(f.shape);

                    Text text(font);
                    text.setString(std::to_string(f.number));
                    text.setCharacterSize(14);
                    text.setFillColor(Color::White);

                    auto bounds = text.getLocalBounds();
                    text.setOrigin(bounds.position + bounds.size / 2.f);
                    text.setPosition(f.shape.getPosition());

                    window.draw(text);

                }
            }
        }

        if (selecting) {
            window.draw(selectionBox);
        }

        window.display();
    }

    return 0;
}

// Puissance4.cpp
#include "Puissance4.h"
#include <iostream>

Puissance4::Puissance4() : board(6, std::vector<char>(7, ' ')), currentPlayer('X'), window(sf::VideoMode(700, 600), "Puissance 4") {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}

void Puissance4::drawBoard() {
    window.clear(sf::Color::White);

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Blue);
    rect.setSize(sf::Vector2f(100, 100));

    sf::CircleShape piece(40);

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            rect.setPosition(col * 100, row * 100);
            window.draw(rect);

            if (board[row][col] != ' ') {
                piece.setFillColor(board[row][col] == 'X' ? sf::Color::Red : sf::Color::Yellow);
                piece.setPosition(col * 100 + 10, row * 100 + 10);
                window.draw(piece);
            }
        }
    }

    window.display();
}

bool Puissance4::checkWin(int row, int col) {
    const int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };
    for (const auto& direction : directions) {
        int dx = direction[0], dy = direction[1];
        int count = 1;
        for (int step = 1; step < 4; ++step) {
            int r = row + step * dx, c = col + step * dy;
            if (r >= 0 && r < 6 && c >= 0 && c < 7 && board[r][c] == currentPlayer) ++count;
            else break;
        }
        for (int step = 1; step < 4; ++step) {
            int r = row - step * dx, c = col - step * dy;
            if (r >= 0 && r < 6 && c >= 0 && c < 7 && board[r][c] == currentPlayer) ++count;
            else break;
        }
        if (count >= 4) return true;
    }
    return false;
}

void Puissance4::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void Puissance4::play() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int col = event.mouseButton.x / 100;

                if (col >= 0 && col < 7) {
                    for (int row = 5; row >= 0; --row) {
                        if (board[row][col] == ' ') {
                            board[row][col] = currentPlayer;
                            if (checkWin(row, col)) {
                                drawBoard();
                                std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                                return;
                            }
                            switchPlayer();
                            break;
                        }
                    }
                }
            }
        }

        drawBoard();
    }
}
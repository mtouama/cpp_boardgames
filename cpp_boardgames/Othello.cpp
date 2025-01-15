// Othello.cpp
#include "Othello.h"
#include <iostream>

Othello::Othello() : board(8, std::vector<char>(8, ' ')), currentPlayer('B'), window(sf::VideoMode(800, 800), "Othello") {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Initialize the starting positions
    board[3][3] = 'W';
    board[3][4] = 'B';
    board[4][3] = 'B';
    board[4][4] = 'W';
}

void Othello::drawBoard() {
    window.clear(sf::Color::Green);

    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0, 100, 0)); // Dark green squares
    rect.setSize(sf::Vector2f(100, 100));

    sf::CircleShape piece(40);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            rect.setPosition(col * 100, row * 100);
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(1);
            window.draw(rect);

            if (board[row][col] != ' ') {
                piece.setFillColor(board[row][col] == 'B' ? sf::Color(50, 50, 50) : sf::Color::White);
                piece.setPosition(col * 100 + 10, row * 100 + 10);
                window.draw(piece);
            }
        }
    }

    window.display();
}

bool Othello::isValidMove(int row, int col) {
    if (board[row][col] != ' ') return false;

    const int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& direction : directions) {
        int dx = direction[0], dy = direction[1];
        int r = row + dx, c = col + dy;
        bool hasOpponentPiece = false;

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c] == ' ') break;
            if (board[r][c] == currentPlayer) {
                if (hasOpponentPiece) return true;
                else break;
            }
            hasOpponentPiece = true;
            r += dx;
            c += dy;
        }
    }

    return false;
}

void Othello::makeMove(int row, int col) {
    if (!isValidMove(row, col)) return;

    board[row][col] = currentPlayer;
    flipPieces(row, col);
}

void Othello::flipPieces(int row, int col) {
    const int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& direction : directions) {
        int dx = direction[0], dy = direction[1];
        int r = row + dx, c = col + dy;
        std::vector<std::pair<int, int>> toFlip;

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c] == ' ') break;
            if (board[r][c] == currentPlayer) {
                for (const auto& pos : toFlip) {
                    board[pos.first][pos.second] = currentPlayer;
                }
                break;
            }
            toFlip.emplace_back(r, c);
            r += dx;
            c += dy;
        }
    }
}

bool Othello::hasValidMoves() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (isValidMove(row, col)) return true;
        }
    }
    return false;
}

void Othello::switchPlayer() {
    currentPlayer = (currentPlayer == 'B') ? 'W' : 'B';
}

void Othello::play() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int row = event.mouseButton.y / 100;
                int col = event.mouseButton.x / 100;

                if (row >= 0 && row < 8 && col >= 0 && col < 8 && isValidMove(row, col)) {
                    makeMove(row, col);
                    switchPlayer();
                    if (!hasValidMoves()) {
                        switchPlayer();
                        if (!hasValidMoves()) {
                            std::cout << "Game Over!" << std::endl;
                            return;
                        }
                    }
                }
            }
        }

        drawBoard();
    }
}

// TicTacToe.cpp
#include "TicTacToe.h"
#include <iostream>

TicTacToe::TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X'), window(sf::VideoMode(600, 600), "Tic Tac Toe") {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}

void TicTacToe::drawBoard() {
    window.clear(sf::Color::White);

    sf::RectangleShape line;
    line.setFillColor(sf::Color::Black);

    // Draw grid lines
    for (int i = 1; i < 3; ++i) {
        // Vertical lines
        line.setSize(sf::Vector2f(5, 600));
        line.setPosition(i * 200 - 2.5, 0);
        window.draw(line);

        // Horizontal lines
        line.setSize(sf::Vector2f(600, 5));
        line.setPosition(0, i * 200 - 2.5);
        window.draw(line);
    }

    // Draw pieces
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Black);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] != ' ') {
                text.setString(board[row][col]);
                text.setPosition(col * 200 + 75, row * 200 + 50);
                window.draw(text);
            }
        }
    }

    window.display();
}

bool TicTacToe::checkWin() {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return true;
        }
    }
    return (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer);
}

bool TicTacToe::checkDraw() {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

void TicTacToe::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void TicTacToe::play() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int row = event.mouseButton.y / 200;
                int col = event.mouseButton.x / 200;

                if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                    board[row][col] = currentPlayer;
                    if (checkWin()) {
                        drawBoard();
                        std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                        return;
                    }
                    else if (checkDraw()) {
                        drawBoard();
                        std::cout << "It's a draw!" << std::endl;
                        return;
                    }
                    switchPlayer();
                }
            }
        }

        drawBoard();
    }
}
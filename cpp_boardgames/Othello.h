// Othello.h
#ifndef OTHELLO_H
#define OTHELLO_H

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Othello : public Game {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;

    sf::RenderWindow window;
    sf::Font font;

    void drawBoard();
    bool isValidMove(int row, int col);
    void makeMove(int row, int col);
    bool hasValidMoves();
    void switchPlayer();
    void flipPieces(int row, int col);

public:
    Othello();
    void play() override;
};

#endif // OTHELLO_H

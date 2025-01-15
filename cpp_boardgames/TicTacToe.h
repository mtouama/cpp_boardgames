// TicTacToe.h
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class TicTacToe : public Game {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;

    sf::RenderWindow window;
    sf::Font font;

    void drawBoard();
    bool checkWin();
    bool checkDraw();
    void switchPlayer();

public:
    TicTacToe();
    void play() override;
};

#endif // TICTACTOE_H
// Puissance4.h
#ifndef PUISSANCE4_H
#define PUISSANCE4_H

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Puissance4 : public Game {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;

    sf::RenderWindow window;
    sf::Font font;

    void drawBoard();
    bool checkWin(int row, int col);
    void switchPlayer();

public:
    Puissance4();
    void play() override;
};

#endif // PUISSANCE4_H#pragma once

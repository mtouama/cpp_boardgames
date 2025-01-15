// Checkers.h
#ifndef CHECKERS_H
#define CHECKERS_H

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Checkers : public Game {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    sf::RenderWindow window;
    sf::Font font;
    sf::Vector2i selectedPiece;
    std::vector<sf::Vector2i> validMoves;

    void drawBoard();
    void drawPieces();
    void drawValidMoves();
    bool isValidMove(int startX, int startY, int endX, int endY);
    void makeMove(int startX, int startY, int endX, int endY);
    void switchPlayer();
    bool hasValidMoves();
    std::vector<sf::Vector2i> getValidMovesForPiece(int x, int y);
    bool isKing(int x, int y) const;
    void checkForKing(int x, int y);
    bool canJumpAgain(int x, int y);

public:
    Checkers();
    virtual ~Checkers() override;
    virtual void play() override;
};

#endif // CHECKERS_H
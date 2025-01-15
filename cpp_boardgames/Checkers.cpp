
// Checkers.cpp
#include "Checkers.h"
#include <iostream>

Checkers::Checkers()
    : board(8, std::vector<char>(8, ' '))
    , currentPlayer('B')
    , window(sf::VideoMode(800, 800), "Checkers")
    , selectedPiece({ -1, -1 }) {

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Warning: Failed to load font" << std::endl;
    }

    // Initialize the board with pieces
    for (int row = 0; row < 3; ++row) {
        for (int col = (row % 2) == 0 ? 1 : 0; col < 8; col += 2) {
            board[row][col] = 'w'; // White pieces (lowercase for regular pieces)
        }
    }
    for (int row = 5; row < 8; ++row) {
        for (int col = (row % 2) == 0 ? 1 : 0; col < 8; col += 2) {
            board[row][col] = 'b'; // Black pieces
        }
    }

    window.setFramerateLimit(60);
}

Checkers::~Checkers() {
    if (window.isOpen()) {
        window.close();
    }
}

void Checkers::drawBoard() {
    window.clear(sf::Color(139, 69, 19)); // Brown background

    sf::RectangleShape square(sf::Vector2f(100, 100));

    // Draw the board squares
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            square.setPosition(col * 100.f, row * 100.f);
            if ((row + col) % 2 == 0) {
                square.setFillColor(sf::Color(255, 206, 158)); // Light square
            }
            else {
                square.setFillColor(sf::Color(209, 139, 71)); // Dark square
            }
            window.draw(square);
        }
    }

    // Highlight selected piece
    if (selectedPiece.x != -1) {
        square.setPosition(selectedPiece.y * 100.f, selectedPiece.x * 100.f);
        square.setFillColor(sf::Color(255, 255, 0, 128)); // Semi-transparent yellow
        window.draw(square);
    }

    drawValidMoves();
    drawPieces();
}

void Checkers::drawValidMoves() {
    sf::CircleShape marker(20);
    marker.setFillColor(sf::Color(0, 255, 0, 128)); // Semi-transparent green

    for (const auto& move : validMoves) {
        marker.setPosition(move.y * 100 + 30, move.x * 100 + 30);
        window.draw(marker);
    }
}

void Checkers::drawPieces() {
    sf::CircleShape piece(40);
    sf::CircleShape kingMarker(15);
    kingMarker.setFillColor(sf::Color::Yellow);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col] != ' ') {
                // Main piece
                piece.setPosition(col * 100 + 10, row * 100 + 10);
                if (tolower(board[row][col]) == 'b') {
                    piece.setFillColor(sf::Color(50, 50, 50)); // Dark gray
                    piece.setOutlineColor(sf::Color::Black);
                }
                else {
                    piece.setFillColor(sf::Color(240, 240, 240)); // Light gray
                    piece.setOutlineColor(sf::Color::White);
                }
                piece.setOutlineThickness(3);
                window.draw(piece);

                // King marker
                if (isupper(board[row][col])) {
                    kingMarker.setPosition(col * 100 + 35, row * 100 + 35);
                    window.draw(kingMarker);
                }
            }
        }
    }
}

bool Checkers::isKing(int x, int y) const {
    return isupper(board[x][y]);
}

void Checkers::checkForKing(int x, int y) {
    if ((currentPlayer == 'B' && x == 0) || (currentPlayer == 'W' && x == 7)) {
        board[x][y] = toupper(board[x][y]);
    }
}

std::vector<sf::Vector2i> Checkers::getValidMovesForPiece(int row, int col) {
    std::vector<sf::Vector2i> moves;

    // Vérifier si la position est valide et si la pièce appartient au joueur actuel
    if (row < 0 || row >= 8 || col < 0 || col >= 8 || board[row][col] == ' ' ||
        tolower(board[row][col]) != tolower(currentPlayer)) {
        return moves;
    }

    std::vector<std::pair<int, int>> directions;
    if (isKing(row, col)) {
        directions = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} }; // Rois : toutes directions
    }
    else if (currentPlayer == 'B') {
        directions = { {-1, -1}, {-1, 1} }; // Noirs : vers le haut
    }
    else {
        directions = { {1, -1}, {1, 1} }; // Blancs : vers le bas
    }

    // Vérifier les déplacements simples
    for (const auto& direction : directions) {
        int dx = direction.first;
        int dy = direction.second;
        int newRow = row + dx;
        int newCol = col + dy;

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (board[newRow][newCol] == ' ') {
                moves.push_back({ newRow, newCol });
            }
            else if (tolower(board[newRow][newCol]) != tolower(currentPlayer)) {
                // Vérifier les sauts possibles
                int jumpRow = newRow + dx;
                int jumpCol = newCol + dy;
                if (jumpRow >= 0 && jumpRow < 8 && jumpCol >= 0 && jumpCol < 8 &&
                    board[jumpRow][jumpCol] == ' ') {
                    moves.push_back({ jumpRow, jumpCol });
                }
            }
        }
    }

    return moves;
}

bool Checkers::isValidMove(int startRow, int startCol, int endRow, int endCol) {
    // Vérifier si les coordonnées sont dans les limites
    if (startRow < 0 || startRow >= 8 || startCol < 0 || startCol >= 8 ||
        endRow < 0 || endRow >= 8 || endCol < 0 || endCol >= 8) {
        return false;
    }

    // Vérifier si la case de destination est vide
    if (board[endRow][endCol] != ' ') {
        return false;
    }

    auto moves = getValidMovesForPiece(startRow, startCol);
    return std::find(moves.begin(), moves.end(), sf::Vector2i(endRow, endCol)) != moves.end();
}

bool Checkers::canJumpAgain(int x, int y) {
    auto moves = getValidMovesForPiece(x, y);
    for (const auto& move : moves) {
        if (abs(move.x - x) == 2) { // If any move is a jump
            return true;
        }
    }
    return false;
}

void Checkers::makeMove(int startRow, int startCol, int endRow, int endCol) {
    if (!isValidMove(startRow, startCol, endRow, endCol)) {
        return;
    }

    // Effectuer le déplacement
    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = ' ';

    // Capturer une pièce si c'est un saut
    if (abs(endRow - startRow) == 2) {
        int middleRow = (startRow + endRow) / 2;
        int middleCol = (startCol + endCol) / 2;
        board[middleRow][middleCol] = ' ';

        // Vérifier s'il y a d'autres sauts possibles
        auto additionalJumps = getValidMovesForPiece(endRow, endCol);
        bool hasMoreJumps = false;
        for (const auto& move : additionalJumps) {
            if (abs(move.x - endRow) == 2) {
                hasMoreJumps = true;
                break;
            }
        }


        if (hasMoreJumps) {
            selectedPiece = { endRow, endCol };
            validMoves = additionalJumps;
            return;
        }
    }

    // Promotion en roi
    if ((currentPlayer == 'B' && endRow == 0) ||
        (currentPlayer == 'W' && endRow == 7)) {
        board[endRow][endCol] = toupper(board[endRow][endCol]);
    }

    // Changer de joueur
    switchPlayer();
}

void Checkers::switchPlayer() {
    currentPlayer = (currentPlayer == 'B') ? 'W' : 'B';
    selectedPiece = { -1, -1 };
    validMoves.clear();
}

bool Checkers::hasValidMoves() {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (tolower(board[x][y]) == tolower(currentPlayer) && !getValidMovesForPiece(x, y).empty()) {
                return true;
            }
        }
    }
    return false;
}

void Checkers::play() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Convertir les coordonnées de la souris en indices du tableau
                int row = event.mouseButton.y / 100;
                int col = event.mouseButton.x / 100;

                // Vérifier que les coordonnées sont valides
                if (row >= 0 && row < 8 && col >= 0 && col < 8) {
                    if (selectedPiece.x == -1 && selectedPiece.y == -1) {
                        // Sélection d'une pièce
                        if (board[row][col] != ' ' && tolower(board[row][col]) == tolower(currentPlayer)) {
                            selectedPiece = { row, col };
                            validMoves = getValidMovesForPiece(row, col);
                        }
                    }
                    else {
                        // Tentative de déplacement
                        if (isValidMove(selectedPiece.x, selectedPiece.y, row, col)) {
                            makeMove(selectedPiece.x, selectedPiece.y, row, col);
                        }
                        // Réinitialiser la sélection dans tous les cas
                        selectedPiece = { -1, -1 };
                        validMoves.clear();
                    }
                }
            }
        }

        drawBoard();
        window.display();

        if (!hasValidMoves()) {
            std::cout << (currentPlayer == 'B' ? "White" : "Black") << " wins!" << std::endl;
            sf::sleep(sf::seconds(3));
            window.close();
        }
    }
}
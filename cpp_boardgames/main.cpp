// main.cpp
#include "TicTacToe.h"
#include "Puissance4.h"
#include "Othello.h"
#include "Checkers.h"
#include <iostream>
#include <memory>

int main() {
    while (true) {
        std::cout << "Choose a game: \n1. Tic Tac Toe\n2. Puissance 4\n3. Othello\n4. Checkers\n5. Exit\nEnter choice: ";
        int choice;
        std::cin >> choice;

        std::unique_ptr<Game> game;

        switch (choice) {
        case 1:
            game = std::make_unique<TicTacToe>();
            break;
        case 2:
            game = std::make_unique<Puissance4>();
            break;
        case 3:
            game = std::make_unique<Othello>();
            break;
        case 4:
            game = std::make_unique<Checkers>();
            break;
        case 5:
            std::cout << "Exiting..." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
            continue;
        }

        game->play();
    }
}
#include <iostream>
#include "game.h"

int main() {
    try {
        std::cout << "Welcome to the Game!\n";

        // Get player names
        std::string player1Name, player2Name;
        std::cout << "Enter Player 1 name: ";
        std::getline(std::cin, player1Name);
        std::cout << "Enter Player 2 name: ";
        std::getline(std::cin, player2Name);

        // Create the game object
        Game game(player1Name, player2Name);

        // Start the game
        game.start();

        std::cout << "Thanks for playing!\n";
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

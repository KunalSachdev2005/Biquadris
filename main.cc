#include <iostream>
#include "game.h"
#include <algorithm>

int main() {
    try {
        std::cout << "Welcome to the Game!\n";

        // Get player names and levels
        std::string player1Name, player2Name;
        int player1Level, player2Level;

        std::cout << "Enter Player 1 name: ";
        std::getline(std::cin, player1Name);

        std::cout << "Enter Player 1 level: ";
        std::cin >> player1Level;

        // Clear the newline character left in the input stream
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter Player 2 name: ";
        std::getline(std::cin, player2Name);

        std::cout << "Enter Player 2 level: ";
        std::cin >> player2Level;

        // Create the game object
        Game game(player1Name, player2Name, player1Level, player2Level);

        // Start the game
        game.start();

        std::cout << "Thanks for playing!\n";
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

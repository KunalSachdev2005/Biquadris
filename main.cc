#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "game.h"

int main(int argc, char* argv[]) {
    try {

        // Default configurations
        bool textMode = false;
        int seed = 0;
        bool seedSet = false;
        std::string scriptFile1 = "sequence1.txt";
        std::string scriptFile2 = "sequence2.txt";
        int startLevel = 0;

        // Parsing cmd-line args
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-text") {
                textMode = true;
            } else if (arg == "-seed") {
                if (i + 1 < argc) { // ensure there seed number is provided
                    seed = std::stoi(argv[++i]);
                    seedSet = true;
                } else {
                    throw std::invalid_argument("Missing value for -seed");
                }
            } else if (arg == "-scriptfile1") {
                if (i + 1 < argc) {
                    scriptFile1 = argv[++i];
                } else {
                    throw std::invalid_argument("Missing value for -scriptfile1");
                }
            } else if (arg == "-scriptfile2") {
                if (i + 1 < argc) {
                    scriptFile2 = argv[++i];
                } else {
                    throw std::invalid_argument("Missing value for -scriptfile2");
                }
            } else if (arg == "-startlevel") {
                if (i + 1 < argc) {
                    startLevel = std::stoi(argv[++i]);
                } else {
                    throw std::invalid_argument("Missing value for -startlevel");
                }
            } else {
                throw std::invalid_argument("Unknown command-line argument: " + arg);
            }

        }

        // Setting random seed if provided
        if (seedSet) {
            srand(seed);
        }

        // Welcome Message
        std::cout << "Welcome to the Game!\n";

        // Get player names
        std::string player1Name, player2Name;
        //int player1Level, player2Level;

        std::cout << "Enter Player 1 name: ";
        std::getline(std::cin, player1Name);

        //std::cout << "Enter Player 1 level: ";
        //std::cin >> player1Level;

        // Clear the newline character left in the input stream
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter Player 2 name: ";
        std::getline(std::cin, player2Name);

        //std::cout << "Enter Player 2 level: ";
        //std::cin >> player2Level;

        // Create the game object
        Game game(player1Name, player2Name, startLevel, scriptFile1, scriptFile2, seed);

        // Start the game
        game.start();

        std::cout << "Thanks for playing!\n";
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

#include <iostream>
#include <iomanip>

#include "textdisplay.h"
#include "game.h"

// Constructor for TextDisplay
TextDisplay::TextDisplay(Game* game) : game(game) {}

// Public method to update the display
void TextDisplay::update() {
    Player* player1 = game->getPlayer1();
    Player* player2 = game->getPlayer2();

    std::cout << std::string(38, '-') << std::endl;

    std::cout << "Level:  " 
            << std::setw(5) << player1->getLevel()->getLevel() 
            << "     ||     Level:  " 
            << std::setw(5) << player2->getLevel()->getLevel() 
            << std::endl;

    // Print Score line
    std::cout << "Score:  " 
            << std::setw(5) << player1->getScore().getScore() 
            << "     ||     Score:  " 
            << std::setw(5) << player2->getScore().getScore() 
            << std::endl;

    // Print High Score line
    std::cout << "High Score: " 
            << player1->getScore().getHighScore() 
            << "     ||     High Score: " 
            <<  player2->getScore().getHighScore() 
            << std::endl;

    // Print boards side by side (first 18 rows)
    printSideBySideBoards(player1, player2);

    // Separator for next block
    std::cout << std::string(38, '-') << std::endl;

    // Print next blocks 
    printNextBlocks(player1, player2);

    std::cout << std::string(38, '-') << std::endl;
}

// Private method to print side-by-side boards (first 18 rows)
void TextDisplay::printSideBySideBoards(Player* player1, Player* player2) {
    std::cout << "+-----------+" << std::string(5, ' ') << "||" << std::string(5, ' ') << "+-----------+" << std::endl;
    for (int r = 0; r < 18; ++r) {
        // Player 1 board rendering
        std::cout << "|";
        
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player1->getBoard()->at(r, c);
            printCell(cell);
        }
        std::cout << "|";

        // Space between boards
        std::cout << std::string(5, ' ') << "||" << std::string(5, ' ');

        // Player 2 board rendering
        std::cout << "|";
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player2->getBoard()->at(r, c);
            printCell(cell);
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+-----------+" << std::string(5, ' ') << "||" << std::string(5, ' ') << "+-----------+" << std::endl;
}

// Private method to print the "next" blocks for both players
void TextDisplay::printNextBlocks(Player* player1, Player* player2) {
    std::cout << "|Next:      |"  << std::string(5, ' ') << "||" << std::string(5, ' ') << "|Next:      |" << std::endl;
    for (int r = 21; r < 24; ++r) {
        // Player 1 board rendering
        std::cout << "|";
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player1->getBoard()->at(r, c);
            printCell(cell);
        }
        std::cout << "|";

        // Space between boards
        std::cout << std::string(5, ' ') << "||" << std::string(5, ' ');

        // Player 2 board rendering
        std::cout << "|";
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player2->getBoard()->at(r, c);
            printCell(cell);
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "*-----------*" << std::string(5, ' ') << "||" << std::string(5, ' ') << "*-----------*" << std::endl;   
}

// Private method to print the visual representation of a cell
void TextDisplay::printCell(Cell* cell) {
    if (cell->isBlind()) {
        std::cout << "?";
    }
    else if (!cell || !cell->isOccupied()) {
        std::cout << " ";
    } else {
        Block* block = cell->getBlock();
        char ch = getBlockTypeChar(block);
        std::cout << ch;
    } 
}

// Private helper function to return the character representation of a block type
char TextDisplay::getBlockTypeChar(Block* block) {
    if (!block) return ' ';
    switch(block->getType()) {
        case Type::I: return 'I';
        case Type::J: return 'J';
        case Type::L: return 'L';
        case Type::O: return 'O';
        case Type::S: return 'S';
        case Type::T: return 'T';
        case Type::Z: return 'Z';
        case Type::SP: return '*';
        default: return ' ';
    }
}

#include "textdisplay.h"
#include "game.h"
#include <iostream>
#include <iomanip>

TextDisplay::TextDisplay(Game* game) : game(game) {}

void TextDisplay::update() {
    Player* player1 = game->getPlayer1();
    Player* player2 = game->getPlayer2();

    // Print scores and levels
    std::cout << "Level:    " 
              << std::setw(5) << player1->getLevel()->getLevel() 
              << std::setw(15) << player2->getLevel()->getLevel() << std::endl;
    
    std::cout << "Score:    " 
              << std::setw(5) << player1->getScore().getScore() 
              << std::setw(15) << player2->getScore().getScore() << std::endl;
    
    std::cout << "Hi Score: " 
              << std::setw(5) << player1->getHighScore().getScore() 
              << std::setw(15) << player2->getHighScore().getScore() << std::endl;

    // Print boards side by side (first 18 rows)
    printSideBySideBoards(player1, player2);

    // Separator for next block
    std::cout << std::string(36, '-') << std::endl;

    // Print next blocks 
    printNextBlocks(player1, player2);
}

void TextDisplay::printSideBySideBoards(Player* player1, Player* player2) {
    std::cout << "+-----------+" << std::string(10, ' ') << "+-----------+" << std::endl;

    for (int r = 0; r < 18; ++r) {
        // Player 1 board rendering
        std::cout << "|";
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player1->getBoard()->at(r, c);
            printCell(cell);
        }
        std::cout << "|";

        // Space between boards
        std::cout << std::string(10, ' ');

        // Player 2 board rendering
        std::cout << "|";
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player2->getBoard()->at(r, c);
            printCell(cell);
        }
        std::cout << "|" << std::endl;
    }

    std::cout << "+-----------+" << std::string(10, ' ') << "+-----------+" << std::endl;
}

void TextDisplay::printCell(Cell* cell) {
    if (!cell || !cell->isOccupied()) {
        std::cout << " ";
    } else {
        Block* block = cell->getBlock();
        char ch = getBlockTypeChar(block);
        std::cout << ch;
    } 
}

void TextDisplay::printNextBlocks(Player* player1, Player* player2) {
    for (int r = 21; r < 24; ++r) {
        // Player 1 board rendering
        std::cout << "|";
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player1->getBoard()->at(r, c);
            printCell(cell);
        }
        std::cout << "|";

        // Space between boards
        std::cout << std::string(10, ' ');

        // Player 2 board rendering
        std::cout << "|";
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player2->getBoard()->at(r, c);
            printCell(cell);
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "*-----------*" << std::string(10, ' ') << "*-----------*" << std::endl;   
}
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
        default: return ' ';
    }
}
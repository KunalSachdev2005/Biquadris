#include "textdisplay.h"
#include <iostream>
#include <iomanip>

// Constructor
TextDisplay::TextDisplay() : 
    board1Display(15, std::vector<char>(11, ' ')), 
    board2Display(15, std::vector<char>(11, ' ')),
    player1Level(0), 
    player2Level(0),
    player1NextBlock(""),
    player2NextBlock("") {}

char TextDisplay::getBlockChar(Type blockType) {
    switch (blockType) {
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

void TextDisplay::renderBoard(const Board* board, std::vector<std::vector<char>>& boardDisplay) {
    // Reset the board display
    for (auto& row : boardDisplay) {
        std::fill(row.begin(), row.end(), ' ');
    }

    // Render the board state
    auto& grid = board->getGrid();
    for (size_t r = 3; r < grid.size(); ++r) {  // Skip the first 3 reserve rows
        for (size_t c = 0; c < grid[r].size(); ++c) {
            if (grid[r][c].isOccupied()) {
                // Map row and column to boardDisplay, adjusting for reserve rows
                boardDisplay[r - 3][c] = getBlockChar(grid[r][c].getBlock()->getType());
            }
        }
    }
}

void TextDisplay::renderNextBlock(Block* nextBlock, std::string& nextBlockDisplay) {
    if (!nextBlock) {
        nextBlockDisplay = "";
        return;
    }

    nextBlockDisplay = "";
    auto shape = nextBlock->getShape();
    Type blockType = nextBlock->getType();
    char blockChar = getBlockChar(blockType);

    // Create a simple representation of the next block
    for (const auto& offset : shape) {
        if (offset.first == 0) {  // Only show horizontal representation
            nextBlockDisplay += blockChar;
        }
    }
}

void TextDisplay::clear() {
    // Reset all display elements
    board1Display = std::vector<std::vector<char>>(15, std::vector<char>(11, ' '));
    board2Display = std::vector<std::vector<char>>(15, std::vector<char>(11, ' '));
    player1NextBlock = "";
    player2NextBlock = "";
}

void TextDisplay::drawBoards(Board* player1Board, Board* player2Board) {
    // Render boards
    renderBoard(player1Board, board1Display);
    renderBoard(player2Board, board2Display);

    // Render next blocks
    renderNextBlock(player1Board->getNextBlock(), player1NextBlock);
    renderNextBlock(player2Board->getNextBlock(), player2NextBlock);

    // Set current levels and scores
    player1Level = player1Board->getCurrentLevel();
    player2Level = player2Board->getCurrentLevel();
}

void TextDisplay::drawScores(Score& player1Score, Score& player2Score) {
    this->player1Score = player1Score;
    this->player2Score = player2Score;
}

void TextDisplay::render() {
    // Clear the screen (platform-dependent)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Display game state for both players
    std::cout << "Level: " << std::setw(2) << player1Level 
              << std::setw(20) << "Level: " << std::setw(2) << player2Level << std::endl;
    
    std::cout << "Score: " << std::setw(2) << player1Score.getScore() 
              << std::setw(20) << "Score: " << std::setw(2) << player2Score.getScore() << std::endl;

    // Draw horizontal separators
    std::cout << "-----------" << std::setw(20) << "-----------" << std::endl;

    // Render boards side by side
    for (size_t r = 0; r < board1Display.size(); ++r) {
        // Player 1 board row
        for (char cell : board1Display[r]) {
            std::cout << (cell == ' ' ? ' ' : cell);
        }
        
        // Spacing between boards
        std::cout << std::setw(10);

        // Player 2 board row
        for (char cell : board2Display[r]) {
            std::cout << (cell == ' ' ? ' ' : cell);
        }
        std::cout << std::endl;
    }

    // Draw horizontal separators again
    std::cout << "-----------" << std::setw(20) << "-----------" << std::endl;

    // Next block previews
    std::cout << "Next:" << std::setw(20) << "Next:" << std::endl;
    std::cout << player1NextBlock << std::setw(20) << player2NextBlock << std::endl;
}

void TextDisplay::showFinalScores(Score& player1Score, Score& player2Score) {
    std::cout << "Final Scores:" << std::endl;
    std::cout << "Player 1: " << player1Score.getScore() << std::endl;
    std::cout << "Player 2: " << player2Score.getScore() << std::endl;
}

void TextDisplay::showInstructions() {
    std::cout << "Biquadris Game Instructions:" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "- left: Move block left" << std::endl;
    std::cout << "- right: Move block right" << std::endl;
    std::cout << "- down: Move block down" << std::endl;
    std::cout << "- clockwise: Rotate block clockwise" << std::endl;
    std::cout << "- counterclockwise: Rotate block counterclockwise" << std::endl;
    std::cout << "- drop: Drop the current block" << std::endl;
    std::cout << "- levelup: Increase difficulty level" << std::endl;
    std::cout << "- leveldown: Decrease difficulty level" << std::endl;
}

#include "board.h"
#include "cell.h"
#include "block.h"

#include <iostream>

// Constructor: Initializes the board with a given number of rows and columns
Board::Board()
    : rowsCleared(0), currentBlock(nullptr), nextBlock(nullptr) {
    // Initialize the grid with 21 rows and 11 columns (3 additional rows for the next block)
    grid.resize(rows, std::vector<Cell>(cols));

    // Initialize all cells in the grid with their coordinates
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = Cell(r, c, this);  // Initialize each cell with its (row, col) coordinates
        }
    }
}

// Accessor methods
std::vector<std::vector<Cell>>& Board::getGrid() {
    return grid;
}

Block* Board::getCurrentBlock() {
    return currentBlock;
}

void Board::setCurrentBlock(Block* block) {
    currentBlock = block;
}

Block* Board::getNextBlock() {
    return nextBlock;
}

void Board::setNextBlock(Block* block) {
    nextBlock = block;
}

/* Block* Board::createBlock() {
    // Create a new block (for simplicity, assume creating an I-block here)
    // This can be expanded to randomize block types later
    return new Block(Type::I, at(0, cols / 2), {{0, 0}, {1, 0}, {2, 0}, {3, 0}}, 1);
} */

bool Board::canMove(Block* block, Direction dir) {
    // Implement logic to check if the block can move in the specified direction
    // For simplicity, always return true for now
    return true;
}

bool Board::canRotate(Block* block, Direction dir) {
    // Implement logic to check if the block can rotate in the specified direction
    // For simplicity, always return true for now
    return true;
}

void Board::moveBlock(Direction dir) {
    if (!canMove(currentBlock, dir)) {
        return; // If it can't move, exit the function
    }

    // Get the current position of the base cell
    int originalRow = currentBlock->getBaseCell()->getRow();
    int originalCol = currentBlock->getBaseCell()->getCol();

    switch (dir) {
        case Direction::Right:
            currentBlock->setBaseCell(at(originalRow, originalCol + 1)); // Right shift
            break;
        case Direction::Left:
            currentBlock->setBaseCell(at(originalRow, originalCol - 1)); // Left shift
            break;
        default:
            // Handle any other direction logic if needed (e.g., down)
            break;
    }

    // After shifting, update the block's position on the board
    currentBlock->placeOnBoard(*this);
}

void Board::rotateBlock(Direction dir) {
    if (canRotate(currentBlock, dir)) {
        // Rotate the block (clockwise or counterclockwise)
        currentBlock->rotate(dir);
    }
}

void Board::dropBlock(Block* block) {
    // Drop the block down to the lowest valid position
    // For simplicity, assume we just set the current block
    currentBlock = block;
}

bool Board::isRowFull(int row) {
    // Check if the row is full
    for (int col = 0; col < cols; ++col) {
        if (grid[row][col].getBlock() == nullptr) {
            return false;
        }
    }
    return true;
}

void Board::clearRow(int row) {
    // Clear the full row by removing blocks and shifting down
    for (int col = 0; col < cols; ++col) {
        grid[row][col].setBlock(nullptr);  // Remove the block from the cell
    }

    // Shift the rows above down
    for (int r = row - 1; r >= 0; --r) {
        for (int c = 0; c < cols; ++c) {
            grid[r + 1][c] = grid[r][c];  // Shift down
            grid[r][c].setBlock(nullptr);  // Clear current cell
        }
    }
    rowsCleared++;
}

Cell* Board::at(int row, int col) {
    // Return the cell at (row, col)
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return &grid[row][col];
    }
    return nullptr;  // Out of bounds
}

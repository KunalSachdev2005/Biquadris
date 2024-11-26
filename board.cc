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

Block* Board::getNextBlock() {
    return nextBlock;
}

void Board::setCurrentBlock(Block* block) {
    currentBlock = block;
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
    // Get the current position of the base cell of the block
    Cell* baseCell = block->getBaseCell();
    const std::vector<std::pair<int, int>>& shape = block->getShape();  // Get the current shape of the block

    // Determine the new positions for the block's cells based on the direction
    for (const auto& offset : shape) {
        int newRow = baseCell->getRow() + offset.first;
        int newCol = baseCell->getCol() + offset.second;

        switch (dir) {
            case Direction::Left:
                newCol--;  // Move left
                break;
            case Direction::Right:
                newCol++;  // Move right
                break;
            case Direction::Down:
                newRow++;  // Move down
                break;
        }

        // Check if the new position is out of bounds
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
            return false;  // The move is out of bounds
        }

        // Check if the cell at the new position is occupied by another block (and not the current block)
        Cell* newCell = at(newRow, newCol);  // Get the cell at the new position
        if (newCell->getBlock() != nullptr && newCell->getBlock() != block) {
            return false;  // Collision detected
        }
    }

    // If all positions are valid, return true
    return true;
}


bool Board::canRotate(Block* block, Direction dir) {
    // Save the current shape and base cell of the block
    std::vector<std::pair<int, int>> originalShape = block->getShape();
    Cell* baseCell = block->getBaseCell();

    // Retrieve the list of all rotation shapes
    const auto& rotations = block->getRotationShapes();

    // Determine the new rotation index based on the direction
    int newRotationIndex = (dir == Direction::Clockwise) ? 
                           (block->getCurrentShapeIndex() + 1) % rotations.size() : 
                           (block->getCurrentShapeIndex() - 1 + rotations.size()) % rotations.size();

    // Get the new shape based on the rotation index
    const std::vector<std::pair<int, int>>& newShape = rotations[newRotationIndex];

    // Check each cell that the rotated block will occupy
    for (const auto& offset : newShape) {
        int newRow = baseCell->getRow() + offset.first;
        int newCol = baseCell->getCol() + offset.second;

        // Check if the new position is within bounds
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
            return false;  // Out of bounds
        }

        // Check for collisions (ensure the cell is either empty or occupied by the same block)
        Cell* newCell = at(newRow, newCol);
        if (newCell->getBlock() != nullptr && newCell->getBlock() != block) {
            return false;  // Collision detected
        }
    }

    // If no issues were found, the rotation is valid
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
            currentBlock->setBaseCell(at(originalRow + 1, originalCol));
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
    // Get the current position of the base cell
    Cell* baseCell = block->getBaseCell();
    int originalRow = baseCell->getRow();
    int originalCol = baseCell->getCol();
    
    // Try to move the block down as far as possible
    while (canMove(block, Direction::Down)) {
        // Move the block down one cell
        baseCell = at(originalRow + 1, originalCol);
        block->setBaseCell(baseCell);
        block->placeOnBoard(*this);  // Update the block's cells on the board
        
        originalRow++;  // Update the row position
    }

    // After the block has dropped to the lowest position, finalize the block's position
    block->placeOnBoard(*this);  // Final placement on the board
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

void Board::printTextDisplay() {
    // Print from the top 21 rows of the grid
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // If the cell is occupied by a block, print its block type letter
            if (grid[r][c].isOccupied()) {
                Type blockType = grid[r][c].getBlock()->getType();
                switch (blockType) {
                    case Type::I:
                        std::cout << 'I';
                        break;
                    case Type::J:
                        std::cout << 'J';
                        break;
                    case Type::L:
                        std::cout << 'L';
                        break;
                    case Type::O:
                        std::cout << 'O';
                        break;
                    case Type::S:
                        std::cout << 'S';
                        break;
                    case Type::T:
                        std::cout << 'T';
                        break;
                    case Type::Z:
                        std::cout << 'Z';
                        break;
                }
            } else {
                // Print a space for empty cells
                std::cout << ' ';
            }
        }
        // Move to the next line after each row
        std::cout << std::endl;
    }
}

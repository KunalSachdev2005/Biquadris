#include <iostream>
#include <set>
#include <map>

#include "board.h"
#include "cell.h"
#include "block.h"

const int BOARD_VALID_ROWS = 21;

// Constructor: Initializes the board with a given number of rows and columns
Board::Board()
    : rowsCleared(0), currentBlock(nullptr), nextBlock(nullptr), blinded(false) {

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

int Board::getRows() {
    return rows;
}

int Board::getCols() {
    return cols;
}

// Mutator methods
bool Board::setCurrentBlock(Block* block) {
    if (block) {
        block->clearOldCells();

        // Game over check: Check if the cells for the new block are already occupied
        for (const auto& offset : block->getShape()) {
            int row = 3 - offset.first;  // Using the initial row where blocks are placed
            int col = 0 + offset.second;

            Cell* cell = at(row, col);
            if (cell && cell->isOccupied()) {
                // Game over condition: block cannot be placed
                return false;
            }
        }

        currentBlock = block;
        currentBlock->setBaseCell(at(3, 0));
    }
    return true;
}

void Board::setNextBlock(Block* block) {
    nextBlock = block;
    nextBlock->setBaseCell(at(23, 0));
}

// Block Management
bool Board::canMove(Block* block, Direction dir) {
    // Get the current position of the base cell of the block
    Cell* baseCell = block->getBaseCell();
    const std::vector<std::pair<int, int>>& shape = block->getShape();  // Get the current shape of the block

    // Determine the new positions for the block's cells based on the direction
    for (const auto& offset : shape) {
        int newRow = baseCell->getRow() - offset.first;  // Add offset
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
        if (newRow < 0 || newRow >= BOARD_VALID_ROWS - 3 || newCol < 0 || newCol >= cols) {
            return false;  // The move is out of bounds
        }

        // Check if the cell at the new position is occupied by another block
        Cell* newCell = at(newRow, newCol);
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
        int newRow = baseCell->getRow() - offset.first;
        int newCol = baseCell->getCol() + offset.second;

        // Check if the new position is within bounds
        if (newRow < 0 || newRow >= BOARD_VALID_ROWS - 3 || newCol < 0 || newCol >= cols) {
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

void Board::moveBlock(Block* block, Direction dir) {
    // Capture the original base cell and shape before moving
    Cell* originalBaseCell = block->getBaseCell();
    const std::vector<std::pair<int, int>>& originalShape = block->getShape();

    // Clear the current cells occupied by the block
    for (const auto& offset : originalShape) {
        int row = originalBaseCell->getRow() - offset.first;
        int col = originalBaseCell->getCol() + offset.second;
        Cell* cell = at(row, col);
        if (cell) {
            cell->setBlock(nullptr);  // Clear the block from the cell
        }
    }

    // Get the current position of the base cell
    int originalRow = originalBaseCell->getRow();
    int originalCol = originalBaseCell->getCol();

    // Move the block's base cell
    switch (dir) {
        case Direction::Right:
            block->setBaseCell(at(originalRow, originalCol + 1)); // Right shift
            break;
        case Direction::Left:
            block->setBaseCell(at(originalRow, originalCol - 1)); // Left shift
            break;
        case Direction::Down:
            block->setBaseCell(at(originalRow + 1, originalCol)); // Down shift
            break;
    }

    // After shifting, update the block's position on the board
    block->placeOnBoard(*this);
}

void Board::rotateBlock(Block* block, Direction dir) {
    block->rotate(dir);
}

void Board::dropBlock(Block* block) {
    // Get the current position of the base cell
    Cell* baseCell = block->getBaseCell();
    int originalRow = baseCell->getRow();
    int originalCol = baseCell->getCol();

    // Try to move the block down as far as possible
    while (canMove(block, Direction::Down)) {
        moveBlock(block, Direction::Down);
    }

    // After the block has dropped to the lowest position, finalize the block's position
    block->placeOnBoard(*this);

    // Important: set currentBlock to nullptr after dropping
    currentBlock = nullptr;
}

// Row Management
bool Board::isRowFull(int row) {
    // Check if the row is full
    for (int col = 0; col < cols; ++col) {
        if (grid[row][col].getBlock() == nullptr) {
            return false;
        }
    }
    return true;
}

int Board::clearRow(int row) {
    // Step 1: Collect all blocks on the board
    std::set<Block*> boardBlocks;
    for (int r = 17; r >= 0; --r) {
        for (int c = 0; c < cols; ++c) {
            Block* block = grid[r][c].getBlock();
            if (block) boardBlocks.insert(block);
        }
    }

    // Step 2: Precompute new base cell positions
    std::map<Block*, Cell*> newBaseCells;
    for (Block* block : boardBlocks) {
        Cell* baseCell = block->getBaseCell();
        newBaseCells[block] = at(baseCell->getRow() + 1, baseCell->getCol());
    }

    // Step 3: Apply new positions to blocks
    for (auto& pair : newBaseCells) {
        Block* block = pair.first;
        Cell* newBaseCell = pair.second;
        block->setBaseCell(newBaseCell);
    }

    // Step 4: Check which blocks are completely off the board
    int blockScore = 0;
    for (Block* block : boardBlocks) {
        int cellsRemaining = 0;
        for (Cell* cell : block->getCells()) {
            if (cell->getRow() < 18) cellsRemaining++;
        }

        if (cellsRemaining == 0) {
            block->clearOldCells();
            blockScore += block->getLevelGenerated();
        }
    }

    return blockScore;
}

// Utility methods
Cell* Board::at(int row, int col) {
    // Return the cell at (row, col)
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return &grid[row][col];
    }
    return nullptr;  // Out of bounds
}

void Board::setBlinded(bool blind) {
    blinded = blind;

    int startRow = 3, endRow = 12;
    int startCol = 3, endCol = 9;

    for (int r = startRow; r < endRow; ++r) {
        for (int c = startCol; c < endCol; ++c) {
            Cell* cell = at(r, c);
            cell->setBlind(blind);
        }
    }
}

bool Board::isBlinded() const {
    return blinded;
}

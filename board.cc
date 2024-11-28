#include "board.h"
#include "cell.h"
#include "block.h"
#include <iostream>
#include <set>

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
    if (block) {
    // Clear the cells previously occupied by the block
    for (const auto& offset : block->getShape()) {
        int row = block->getBaseCell()->getRow() - offset.first;
        int col = block->getBaseCell()->getCol() + offset.second;

        Cell* cell = at(row, col);
        if (cell) {
            cell->setBlock(nullptr);
            }   
        }
    }
    currentBlock = block;
    currentBlock->setBaseCell(at(4,0));
}

void Board::setNextBlock(Block* block) {
    nextBlock = block;
    nextBlock->setBaseCell(at(20,0));
}

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
        if (newRow < 0 || newRow >= rows-3 || newCol < 0 || newCol >= cols) {
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
        if (newRow < 0 || newRow >= rows-3 || newCol < 0 || newCol >= cols) {
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
            std::cout<<"Changing base cell.";
            block->setBaseCell(at(originalRow + 1, originalCol)); // Down shift
            break;
    }

    // After shifting, update the block's position on the board
    block->placeOnBoard(*this);
}


void Board::rotateBlock(Block* block, Direction dir) {
    if (canRotate(block, dir)) {
        // Rotate the block (clockwise or counterclockwise)
        block->rotate(dir);
    }
}

void Board::dropBlock(Block* block) {
    std::cout << "Dropping block at base cell: (" 
              << block->getBaseCell()->getRow() << ", " 
              << block->getBaseCell()->getCol() << ")" << std::endl;

    // Get the current position of the base cell
    Cell* baseCell = block->getBaseCell();
    int originalRow = baseCell->getRow();
    int originalCol = baseCell->getCol();

    // Try to move the block down as far as possible
    int dropCount = 0;
    while (canMove(block, Direction::Down)) {
        moveBlock(block, Direction::Down);
        dropCount++;
        std::cout << "Dropped block down. Current position: (" 
                  << block->getBaseCell()->getRow() << ", " 
                  << block->getBaseCell()->getCol() << ")" << std::endl;
    }

    std::cout << "Block dropped " << dropCount << " times" << std::endl;

    // After the block has dropped to the lowest position, finalize the block's position
    block->placeOnBoard(*this);  // Final placement on the board
    
    std::cout << "Block placed on board" << std::endl;
    
    // Important: set currentBlock to nullptr after dropping
    currentBlock = nullptr;
    
    std::cout << "Current block set to nullptr" << std::endl;
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

int Board::clearRow(int row) {
    std::set<Block*> blocksToRemove;
    std::set<Block*> blocksToModify;
    
    // Identify blocks that are in the row and need modification
    for (int col = 0; col < cols; ++col) {
        Cell* cell = &grid[row][col];
        Block* blockAtCell = cell->getBlock();
        
        if (blockAtCell) {
            blocksToModify.insert(blockAtCell);
        }
    }
    
    // Modify shapes of affected blocks
    for (Block* block : blocksToModify) {
        std::vector<std::pair<int, int>> newShape;
        bool blockCompletelyRemoved = true;
        
        // Recalculate the shape, removing offsets at the cleared row
        for (const auto& offset : block->getShape()) {
            int blockRow = block->getBaseCell()->getRow() - offset.first;
            
            // Skip offsets in the cleared row
            if (blockRow != row) {
                // Adjust offset if it was below the cleared row
                if (blockRow > row) {
                    newShape.push_back(std::make_pair(offset.first + 1, offset.second));
                } else {
                    newShape.push_back(offset);
                }
                blockCompletelyRemoved = false;
            }
        }
        
        // If block is completely removed
        if (blockCompletelyRemoved) {
            blocksToRemove.insert(block);
            continue;
        }
        
        // Update the block's shape
        block->setShape(newShape);
    }
    
    // Shift rows down
    for (int r = row; r > 0; --r) {
        for (int c = 0; c < cols; ++c) {
            // Move cell data from row above
            grid[r][c] = grid[r-1][c];
            grid[r][c].setRowCol(r, c);
        }
    }
    
    // Clear the top row
    for (int c = 0; c < cols; ++c) {
        grid[0][c] = Cell(0, c, this);
    }
    
    // Calculate score based on blocks completely removed
    int scoreToAdd = 0;
    for (Block* block : blocksToRemove) {
        scoreToAdd += block->getLevelGenerated();
    }
    
    return scoreToAdd;
}



Cell* Board::at(int row, int col) {
    // Return the cell at (row, col)
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return &grid[row][col];
    }
    return nullptr;  // Out of bounds
}

int Board::getRows() { return rows; }

int Board::getCols() { return cols; }
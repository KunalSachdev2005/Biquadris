#include "block.h"
#include "cell.h"
#include "direction.h"
#include "board.h"
#include <iostream>

const int DEFAULT_WEIGHT = 0;

// Constructor: Initializes block with base cell and shape offsets
Block::Block(Type type, Cell* baseCell, const std::vector<std::pair<int, int>>& shape, int levelGenerated, bool heavy)
    : type(type), baseCell(baseCell), shape(shape), levelGenerated(levelGenerated), heavy(heavy), weight(DEFAULT_WEIGHT), currentShapeIndex(0) {
    // When the block is created, it is placed on the board automatically
    placeOnBoard(baseCell->getBoard());  // Assuming baseCell has a pointer to the board
}

// Destructor: No dynamic memory to free because we're not creating new cells
Block::~Block() {
    // No dynamic memory to clean up
}

// Accessor methods
Type Block::getType() const {
    return type;
}

bool Block::isHeavy() const {
    return heavy;
}

int Block::getWeight() const {
    return weight;
}

int Block::getLevelGenerated() const {
    return levelGenerated;
}

const std::vector<Cell*>& Block::getCells() const {
    return cells;
}

Cell* Block::getBaseCell() const {
    return baseCell;
}

const std::vector<std::pair<int, int>>& Block::getShape() const {
    return shape;
}

void Block::clearOldCells() {
    for (Cell* cell : cells) {
        if (cell) {
            cell->setBlock(nullptr);  // Clear the block from the cell
        }
    }
    cells.clear();  // Reset the cells vector
}

void Block::setShape(const std::vector<std::pair<int, int>>& newShape) {
    // Clear old cells associated with the block
    clearOldCells();

    // Update the shape
    shape = newShape;

    // If the shape is not empty, reapply the block on the board
    if (!shape.empty() && baseCell) {
        placeOnBoard(baseCell->getBoard());
    }
}

// Set base cell
void Block::setBaseCell(Cell* base) {
    clearOldCells();
    baseCell = base;
    placeOnBoard(base->getBoard());  // Recalculate block's position when base is set
}

// Place the block on the board based on the base cell and shape offsets
void Block::placeOnBoard(Board& board) {
    

    cells.clear();  // Clear any previously set cells

    // Loop through each offset in the shape
    for (const auto& offset : shape) {
        int new_row = baseCell->getRow() - offset.first;  
        int new_col = baseCell->getCol() + offset.second; 

       

        // Ensure the new position is within bounds
        if (new_row >= 0 && new_row < board.getRows() && new_col >= 0 && new_col < board.getCols()) {
            Cell* cell = board.at(new_row, new_col);
            if (cell == nullptr) {
                std::cerr << "ERROR: Null cell at (" << new_row << ", " << new_col << ")" << std::endl;
                continue;
            }
            cells.push_back(cell);
        } else {
            std::cerr << "ERROR: Cell out of bounds: (" << new_row << ", " << new_col << ")" << std::endl;
        }
    }

    // After placing the block on the board, update all its cells
    updateCells();
    
   
}

// Update the cells occupied by the block, linking them to this block
void Block::updateCells() {
    for (Cell* cell : cells) {
        cell->setBlock(this);  // Set the block pointer in each cell
    }
}

void Block::initializeRotations(const std::vector<std::vector<std::pair<int, int>>>& rotations) {
    this->rotations = rotations;
}

void Block::rotate(Direction dir) {
    if (rotations.empty()) return;  // No rotations defined, do nothing

    // Track the old cells and clear them
    Board& board = baseCell->getBoard();
    std::vector<Cell*> oldCells = cells;
    for (Cell* cell : oldCells) {
        if (cell) {
            cell->setBlock(nullptr);  // Clear the block from previously occupied cells
        }
    }

    // Update the shape index
    if (dir == Direction::Clockwise) {
        currentShapeIndex = (currentShapeIndex + 1) % rotations.size();
    } else if (dir == Direction::CounterClockwise) {
        currentShapeIndex = (currentShapeIndex - 1 + rotations.size()) % rotations.size();
    }

    // Apply the new shape
    shape = rotations[currentShapeIndex];

    // Reposition the block on the board
    placeOnBoard(board);
}

const std::vector<std::vector<std::pair<int, int>>>& Block::getRotationShapes() const {
    return rotations;
}

// Setter for heavy attribute
void Block::setHeavy(bool heavy) {
    this->heavy = heavy;
}

// Setter for weight attribute
void Block::setWeight(int weight) {
    this->weight = weight;
}

int Block::getCurrentShapeIndex() const {
    return currentShapeIndex;
}

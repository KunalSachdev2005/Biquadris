#include "block.h"
#include "cell.h"
#include "direction.h"
#include "board.h"

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

// Set base cell
void Block::setBaseCell(Cell* base) {
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

        // Get the corresponding cell from the board and add to the cells vector
        Cell* cell = board.at(new_row, new_col);
        cells.push_back(cell);  // Add the cell to the block's cells vector
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

// Setter for heavy attribute
void Block::setHeavy(bool heavy) {
    this->heavy = heavy;
}

// Setter for weight attribute
void Block::setWeight(int weight) {
    this->weight = weight;
}

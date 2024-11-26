#include "Block.h"

// Constructor: Initializes block with base cell and shape offsets
Block::Block(Type type, Cell* baseCell, const std::vector<std::pair<int, int>>& shape, int levelGenerated, bool heavy)
    : type(type), baseCell(baseCell), shape(shape), levelGenerated(levelGenerated), heavy(heavy), weight(0) {
    // When the block is created, it is placed on the board automatically
    placeOnBoard(*baseCell->getBoard());  // Assuming baseCell has a pointer to the board
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

const std::vector<std::pair<int, int>>& Block::getShape() const {
    return shape;
}

// Set base cell
void Block::setBaseCell(Cell* base) {
    baseCell = base;
    placeOnBoard(*base->getBoard());  // Recalculate block's position when base is set
}

// Place the block on the board based on the base cell and shape offsets
void Block::placeOnBoard(Board& board) {
    cells.clear();  // Clear any previously set cells

    // Loop through each offset in the shape
    for (const auto& offset : shape) {
        int r = baseCell->getCol() + offset.first;  // Calculate x position
        int c = baseCell->getRow() + offset.second; // Calculate y position

        // Get the corresponding cell from the board and add to the cells vector
        Cell* cell = board.at(r, c); // Assuming Board has a method to return a cell by coordinates
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


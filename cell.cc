#include "cell.h"
#include "block.h"

// Constructor
Cell::Cell(int row, int col) : row(row), col(col), block(nullptr) {}

// Accessor methods
int Cell::getRow() const {
    return row;
}

int Cell::getCol() const {
    return col;
}

Block* Cell::getBlock() const {
    return block;
}

// Mutator methods
void Cell::setBlock(Block* block) {
    this->block = block;
}

void Cell::clear() {
    block = nullptr; // clear the block occupying the cell
}

// Utility method
bool Cell::isOccupied() const {
    return block != nullptr;
}

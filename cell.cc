#include "cell.h"
#include "block.h"
#include "board.h"

// Constructor
Cell::Cell(int row, int col, Board* board) : row(row), col(col), block(nullptr), board(board) { 
    blind = false; 
}

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

Board& Cell::getBoard() const {
    return (*board);
}

// Mutator methods
void Cell::setBlock(Block* block) {
    this->block = block;
}

void Cell::setRowCol(int row, int col) {
    this->row = row;
    this->col = col;
}

void Cell::clear() {
    block = nullptr;  // clear the block occupying the cell
}

// Utility methods
bool Cell::isOccupied() const {
    return block != nullptr;
}

bool Cell::isBlind() const { 
    return blind; 
}

void Cell::setBlind(bool b) {
    blind = b;
}

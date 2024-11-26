#include "TBlock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the TBlock at a given level and base cell
TBlock::TBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::T, baseCell, {{0, 0}, {1, 0}, {2, 1}, {1, 1}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
}

// Override the rotate method for TBlock
void TBlock::rotate(Direction dir) {
    
}

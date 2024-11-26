#include "OBlock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the OBlock at a given level and base cell
OBlock::OBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::L, baseCell, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
}

// Override the rotate method for OBlock
void OBlock::rotate(Direction dir) {
    
}

#include "lBlock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the LBlock at a given level and base cell
LBlock::LBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::L, baseCell, {{2, 0}, {2, 1}, {1, 1}, {0, 1}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
}

// Override the rotate method for LBlock
void LBlock::rotate(Direction dir) {
    
}

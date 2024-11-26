#include "SBlock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the SBlock at a given level and base cell
SBlock::SBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::S, baseCell, {{1, 0}, {2, 0}, {0, 1}, {1, 1}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
}

// Override the rotate method for SBlock
void SBlock::rotate(Direction dir) {
    
}

#include "jBlock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the JBlock at a given level and base cell
JBlock::JBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::J, baseCell, {{0, 0}, {0, 1}, {1, 1}, {2, 1}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
}

// Override the rotate method for JBlock
void JBlock::rotate(Direction dir) {
    
}

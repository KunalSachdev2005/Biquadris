#include "board.h"
#include "specialblock.h"

// Constructor: Initializes the SBlock at a given level and base cell
SPBlock::SPBlock(Cell* baseCell)
    : Block(Type::SP, baseCell, {{0, 0}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
    initializeRotations({
        {{0, 0}}  // Default horizontal
    });
}

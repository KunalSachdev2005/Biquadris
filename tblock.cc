#include "tblock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the TBlock at a given level and base cell
TBlock::TBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::T, baseCell, {{1, 0}, {1, 1}, {1, 2}, {0, 1}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
    initializeRotations({
        {{1, 0}, {1, 1}, {1, 2}, {0, 1}},  // Default (horizontal)
        {{0, 1}, {1, 1}, {2, 1}, {1, 0}},  // 90 degrees clockwise
        {{1, 0}, {1, 1}, {1, 2}, {2, 1}},  // 180 degrees clockwise
        {{0, 1}, {1, 1}, {2, 1}, {1, 2}}   // 270 degrees clockwise
    });
}


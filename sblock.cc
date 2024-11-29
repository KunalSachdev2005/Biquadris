#include "sblock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the SBlock at a given level and base cell
SBlock::SBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::S, baseCell, {{0, 0}, {0, 1}, {1, 1}, {1, 2}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
    initializeRotations({
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}},  // Default horizontal
        {{0, 1}, {1, 0}, {1, 1}, {2, 0}}   // Vertical orientation
    });
}

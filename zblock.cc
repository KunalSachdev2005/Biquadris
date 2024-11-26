#include "ZBlock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the ZBlock at a given level and base cell
ZBlock::ZBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::Z, baseCell, {{1, 0}, {1, 1}, {0, 1}, {0, 2}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
    initializeRotations({
        {{1, 0}, {1, 1}, {0, 1}, {0, 2}},  // Default horizontal
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}}   // Vertical orientation
    });
}

#include "lblock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the LBlock at a given level and base cell
LBlock::LBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::L, baseCell, {{0, 0}, {0, 1}, {0, 2}, {1, 2}}, levelGenerated) {
    // Define all possible rotations
    initializeRotations({
        {{0, 0}, {0, 1}, {0, 2}, {1, 2}},  // Default shape
        {{0, 0}, {1, 0}, {2, 0}, {0, 1}},  // Rotate 90 degrees clockwise
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},  // Rotate 180 degrees
        {{0, 1}, {1, 1}, {2, 1}, {2, 0}}   // Rotate 270 degrees clockwise
    });
}


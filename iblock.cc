#include "iblock.h"
#include "board.h"
#include "cell.h"

// Constructor
IBlock::IBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::I, baseCell, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, levelGenerated) {
    // Define all rotations for IBlock
    initializeRotations({
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},  // Default horizontal
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}}   // Vertical orientation
    });
}



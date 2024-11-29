#include "jblock.h"

JBlock::JBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::J, baseCell, {{0, 0}, {1, 0}, {0, 1}, {0, 2}}, levelGenerated) {
    // Define all rotations for JBlock
    initializeRotations({
        {{0, 0}, {1, 0}, {0, 1}, {0, 2}},  // Default shape
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}},  // 90 degrees clockwise
        {{1, 0}, {1, 1}, {1, 2}, {0, 2}},  // 180 degrees
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}}   // 270 degrees clockwise
    });
}

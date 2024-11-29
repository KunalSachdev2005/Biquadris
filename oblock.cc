#include "oblock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the OBlock at a given level and base cell
OBlock::OBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::O, baseCell, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, levelGenerated) {
    initializeRotations({
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}}  // Default shape
    });
}

#include "jBlock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the JBlock at a given level and base cell
JBlock::JBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::J, baseCell, {{0, 0}, {1, 0}, {0, 1}, {0, 2}}, levelGenerated), currentShapeIndex(0) {
    rotations = {
        {{0, 0}, {1, 0}, {0, 1}, {0, 2}},  // Default shape
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}},  // Rotate 90 degrees clockwise
        {{1, 0}, {1, 1}, {1, 2}, {0, 2}},  // Rotate 180 degrees
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}}   // Rotate 270 degrees clockwise
    };
}

// Override the rotate method for JBlock
void JBlock::rotate(Direction dir) {
    Board& board = baseCell->getBoard();
    std::vector<Cell*> oldCells = cells;

    // Clear the block from the old cells
    for (Cell* cell : oldCells) {
        if (cell) {
            cell->setBlock(nullptr);
        }
    }

    if (dir == Direction::Clockwise) {
        currentShapeIndex = (currentShapeIndex + 1) % 4;  // Cycle to the next shape
    } else if (dir == Direction::CounterClockwise) {
        currentShapeIndex = (currentShapeIndex + 3) % 4;  // Cycle to the previous shape
    }
    
    shape = rotations[currentShapeIndex];
    placeOnBoard(board);
}
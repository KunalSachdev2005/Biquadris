#include "iBlock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the IBlock at a given level and base cell
IBlock::IBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::I, baseCell, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
    // The I-block occupies 4 cells in a row.
}

// Override the rotate method for IBlock
void IBlock::rotate(Direction dir) {
    // Rotating the I block involves switching between a vertical and horizontal orientation.
    if (dir == Direction::Clockwise || dir == Direction::CounterClockwise) {
        // The I-block rotates 90 degrees, changing its shape from 4 horizontal cells to 4 vertical cells (or vice versa).
        std::vector<std::pair<int, int>> newShape;

        // If the block is in horizontal orientation, change to vertical and vice versa.
        if (shape.size() == 4 && shape[1].first == 0) { // Assuming shape is horizontal initially
            newShape = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};  // Vertical position
        } else {
            newShape = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};  // Horizontal position
        }

        // Update the block's shape after rotation
        shape = newShape;
    }

    // After rotating, update the block's cells on the board
    placeOnBoard(baseCell->getBoard());
}

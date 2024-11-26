#include "iblock.h"
#include "board.h"
#include "cell.h"

// Constructor: Initializes the IBlock at a given level and base cell
IBlock::IBlock(int levelGenerated, Cell* baseCell)
    : Block(Type::I, baseCell, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, levelGenerated) {
    // Here, the block's shape is defined relative to the base cell.
    // The I-block occupies 4 cells in a row.
}

// Override the rotate method for IBlock
void IBlock::rotate(Direction dir) {
    Board& board = baseCell->getBoard();
    std::vector<std::pair<int, int>> newShape;
    std::vector<Cell*> oldCells = cells;

    if(shape[1].first == 0) {
        newShape = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    }
    else {
        newShape = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    }
    
    shape = newShape;

    for (Cell* cell : oldCells) {
        if (cell) {
            cell->setBlock(nullptr);  // Clear the block from previously occupied cells
        }
    }
    // After rotating, update the block's cells on the board
    placeOnBoard(board);
}

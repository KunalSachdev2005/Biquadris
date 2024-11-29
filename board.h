#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "direction.h"

// Constants
const int BOARD_ROWS = 24;
const int BOARD_COLS = 11;

// Forward Declarations
class Block; // Forward Declaration
class Cell;

class Board {

private:
    // Board Grid
    std::vector<std::vector<Cell>> grid;   // 2D grid of cells on the board (18 rows + 3 additional rows for next block)
    
    // Blocks
    std::vector<Block*> blocks;            // Vector of all blocks created in the game
    Block* currentBlock;                   // The current active block
    Block* nextBlock;                      // The next block to appear
    
    // Game State
    int rowsCleared;                       // Number of rows cleared
    bool blinded;                          // Whether the board is blinded or not
    
    // Constants for board dimensions
    const int rows = BOARD_ROWS;           // Number of rows (main game area)
    const int cols = BOARD_COLS;           // Number of columns

public:
    // Constructor
    Board();

    // Accessor methods
    std::vector<std::vector<Cell>>& getGrid();
    int getRows();
    int getCols();
    Block* getCurrentBlock();
    Block* getNextBlock();

    // Mutator methods
    bool setCurrentBlock(Block* block);
    void setNextBlock(Block* block);
    
    // Block Management
    Block* createBlock();
    bool canMove(Block* block, Direction dir);
    bool canRotate(Block* block, Direction dir);
    void moveBlock(Block* block, Direction dir);
    void rotateBlock(Block* block, Direction dir);
    void dropBlock(Block* block);
    
    // Row Management
    bool isRowFull(int row);
    int clearRow(int row);
    
    // Utility methods
    Cell* at(int row, int col);  // Get the cell at (row, col)

    // Blinded State
    void setBlinded(bool blind);
    bool isBlinded() const;
};

#endif

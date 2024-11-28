#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <queue>
#include "direction.h"

const int BOARD_ROWS = 24;
const int BOARD_COLS = 11;

class Block; // Forward Declaration
class Cell;

class Board {

private:
    std::vector<std::vector<Cell>> grid;   // 2D grid of cells on the board (18 rows + 3 additional rows for next block)
    std::vector<Block*> blocks;            // Vector of all blocks created in the game
    Block* currentBlock;                   // The current active block
    Block* nextBlock;                      // The next block to appear
    int rowsCleared;                       // Number of rows cleared
    //std::queue<SpecialAction*> specialActionsQueue;  // Queue of special actions
    //Player* player;                        // The current player
    const int rows = BOARD_ROWS;                   // Number of rows (main game area)
    const int cols = BOARD_COLS;                   // Number of columns

    bool blinded;

public:
    //Board(Player* player);
    Board();
    // Accessor methods
    std::vector<std::vector<Cell>>& getGrid();
    int getRows();
    int getCols();
    Block* getCurrentBlock();
    void setCurrentBlock(Block* block);
    Block* getNextBlock();
    void setNextBlock(Block* block);
    Block* createBlock();
    bool canMove(Block* block, Direction dir);
    bool canRotate(Block* block, Direction dir);
    void moveBlock(Block* block, Direction dir);
    void rotateBlock(Block* block, Direction dir);
    void dropBlock(Block* block);
    bool isRowFull(int row);
    int clearRow(int row);
    //void queueSpecialAction(SpecialAction* action);
    //void applySpecialActions();
    Cell* at(int row, int col);  // Get the cell at (row, col)
    void printTextDisplay();

    void setBlinded(bool blind);
    bool isBlinded() const;
};

#endif

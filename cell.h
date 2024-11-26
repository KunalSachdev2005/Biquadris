#ifndef CELL_H
#define CELL_H

const int DEFAULT_ROW = 0;
const int DEFAULT_COL = 0;

class Board; // Forward Declaration
class Block; // Forward Declaration

class Cell {

private:
    int row;
    int col;
    Block* block;
    Board* board;

public:
    // Constructor
    Cell(int row = DEFAULT_ROW, int col = DEFAULT_COL, Board* board = nullptr);

    // Accessor methods
    int getRow() const;
    int getCol() const;

    Board& getBoard() const;
    
    Block* getBlock() const;

    // Mutator methods
    void setBlock(Block* block);
    void clear();

    // Utility method
    bool isOccupied() const;
};

#endif // CELL_H

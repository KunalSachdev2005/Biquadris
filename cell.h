#ifndef CELL_H
#define CELL_H

// Forward Declarations
class Board; 
class Block; 

// Constants
const int DEFAULT_ROW = 0;
const int DEFAULT_COL = 0;

class Cell {

private:
    // Member Variables
    int row;
    int col;
    Block* block;
    Board* board;
    bool blind;

public:
    // Constructor
    Cell(int row = DEFAULT_ROW, int col = DEFAULT_COL, Board* board = nullptr);

    // Accessor Methods
    int getRow() const;
    int getCol() const;
    Board& getBoard() const;
    Block* getBlock() const;

    // Mutator Methods
    void setRowCol(int row, int col);
    void setBlock(Block* block);
    void clear();

    // Utility Methods
    bool isOccupied() const;
    bool isBlind() const;
    void setBlind(bool b);

};

#endif // CELL_H

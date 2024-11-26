#ifndef CELL_H
#define CELL_H

class Board;
class Block;

class Cell {

private:
    int row;
    int col;
    Block* block;
    Board* board;

public:
    // Constructor
    Cell(int row=0, int col=0, Board* board = nullptr);

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

#endif

#ifndef CELL_H
#define CELL_H

class Block; // forward declaration

class Cell {
    int row;
    int col;
    Block * block;

public:
    // Constructor
    Cell(int row, int col);

    // Accessor methods
    int getRow() const;
    int getCol() const;
    Block* getBlock() const;

    // Mutator methods
    void setBlock(Block* block);
    void clear();

    // Utility method
    bool isOccupied() const;
};

#endif

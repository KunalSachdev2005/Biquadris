#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <utility>

#include "type.h"
#include "direction.h"

class Cell; // Forward Declaration
class Board;

class Block { // Abstract Base Class
    protected:
        std::vector<Cell*> cells;                // Cells occupied by the block on the board
        Cell* baseCell;                          // The top-left cell where the block is placed on the board
        std::vector<std::pair<int, int>> shape;  // Offsets from the base cell to define the block's shape
        Type type;                               // Block type (I, J, L, etc.)
        bool heavy;                              // Whether the block is heavy
        int weight;                              // Weight for block fall behavior
        int levelGenerated;                      // The level at which the block was generated

        std::vector<std::vector<std::pair<int, int>>> rotations;
        int currentShapeIndex;

    public:
        // Constructor that initializes the block at a given base cell on the board
        Block(Type type, Cell* baseCell, const std::vector<std::pair<int, int>>& shape, int levelGenerated, bool heavy = false);

        // Virtual destructor
        virtual ~Block();
        void clearOldCells();

        // Accessor methods
        Type getType() const;                       // Getter for the block type
        bool isHeavy() const;                       // Getter for the heavy attribute
        int getWeight() const;                      // Getter for the weight of the block
        int getLevelGenerated() const;              // Getter for the level at which the block was generated
        int getCurrentShapeIndex() const;           // Getter for the current shape index
        Cell* getBaseCell() const;                  // Getter for the base cell (top-left corner)
        const std::vector<Cell*>& getCells() const; // Getter for the cells occupied by the block
        const std::vector<std::pair<int, int>>& getShape() const; // Getter for the block's shape

        // Mutator methods
        void setShape(const std::vector<std::pair<int, int>>& newShape); // Setter for the block's shape
        void setBaseCell(Cell* base);        // Setter for the base cell (to update its position)
        void setHeavy(bool heavy);           // Setter for the heavy attribute
        void setWeight(int weight);          // Setter for the weight of the block

        // Block Management
        void placeOnBoard(Board& board);     // Place the block on the board
        void updateCells();                  // Update the cells occupied by the block, linking them to this block

        // Rotation-related methods
        void initializeRotations(const std::vector<std::vector<std::pair<int, int>>>& rotations); // Initialize rotations
        const std::vector<std::vector<std::pair<int, int>>>& getRotationShapes() const;           // Getter for rotation shapes
        void rotate(Direction direction);       // Rotate the block (using Direction)
};

#endif // BLOCK_H

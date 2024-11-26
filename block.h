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

        // Accessor methods
        Type getType() const;
        bool isHeavy() const;
        int getWeight() const;
        int getLevelGenerated() const;
        int getCurrentShapeIndex() const;
        Cell* getBaseCell() const;
        const std::vector<Cell*>& getCells() const;
        const std::vector<std::pair<int, int>>& getShape() const;

        // Set the base cell for the block (to update its position)
        void setBaseCell(Cell* base);

        // Place the block on the board
        void placeOnBoard(Board& board);

        // Update the cells occupied by the block, linking them to this block
        void updateCells();

        void initializeRotations(const std::vector<std::vector<std::pair<int, int>>>& rotations); // Initialize rotations

        const std::vector<std::vector<std::pair<int, int>>>& getRotationShapes() const;

        // Rotate the block (using Direction)
        void rotate(Direction direction);

        // Setter for heavy attribute
        void setHeavy(bool heavy);
};

#endif // BLOCK_H

#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"
#include "direction.h"

class LBlock : public Block {
public:
    // Constructor
    LBlock(int levelGenerated, Cell* baseCell);

    // Override rotation method
    void rotate(Direction dir) override;
};

#endif // LBLOCK_H

#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"
#include "direction.h"

class SBlock : public Block {
public:
    // Constructor
    SBlock(int levelGenerated, Cell* baseCell);

    // Override rotation method
    void rotate(Direction dir) override;
};

#endif // SBLOCK_H

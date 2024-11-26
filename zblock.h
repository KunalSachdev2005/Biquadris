#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"

class ZBlock : public Block {
public:
    // Constructor
    ZBlock(int levelGenerated, Cell* baseCell);

    // Override rotation method
    void rotate(Direction dir) override;
};

#endif

#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"
#include "direction.h"

class ZBlock : public Block {
public:
    // Constructor
    ZBlock(int levelGenerated, Cell* baseCell);
};

#endif // ZBLOCK_H

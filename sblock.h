#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"
#include "direction.h"

class SBlock : public Block {
public:
    // Constructor
    SBlock(int levelGenerated, Cell* baseCell);
};

#endif // SBLOCK_H

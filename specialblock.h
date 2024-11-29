#ifndef SPBLOCK_H
#define SPBLOCK_H

#include "block.h"
#include "direction.h"

class SPBlock : public Block {
public:
    // Constructor
    SPBlock(Cell* baseCell);
};

#endif // SPBLOCK_H

#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"
#include "direction.h"

class LBlock : public Block {
public:
    // Constructor
    LBlock(int levelGenerated, Cell* baseCell);
};

#endif // LBLOCK_H

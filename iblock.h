#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"
#include "direction.h"

class IBlock : public Block {
public:
    // Constructor
    IBlock(int levelGenerated, Cell* baseCell);
};

#endif // IBLOCK_H

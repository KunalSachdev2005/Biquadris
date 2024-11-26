#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"
#include "direction.h"

class OBlock : public Block {
public:
    // Constructor
    OBlock(int levelGenerated, Cell* baseCell);
};

#endif // OBLOCK_H

#ifndef TBLOCK_H
#define TBLOCK_H

#include "block.h"
#include "direction.h"

class TBlock : public Block {
public:
    // Constructor
    TBlock(int levelGenerated, Cell* baseCell);
};

#endif // TBLOCK_H

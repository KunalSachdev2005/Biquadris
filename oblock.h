#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"
#include "direction.h"

class OBlock : public Block {
public:
    // Constructor
    OBlock(int levelGenerated, Cell* baseCell);

    // Override rotation method
    void rotate(Direction dir) override;
};

#endif // OBLOCK_H

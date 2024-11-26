#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"


class JBlock : public Block {
public:
    // Constructor
    JBlock(int levelGenerated, Cell* baseCell);
};

#endif // JBLOCK_H

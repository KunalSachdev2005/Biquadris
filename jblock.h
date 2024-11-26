#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"
#include "direction.h"

class JBlock : public Block {
private:
    std::vector<std::vector<std::pair<int, int>>> rotations;
    int currentShapeIndex;
public:
    // Constructor
    JBlock(int levelGenerated, Cell* baseCell);

    // Override rotation method
    void rotate(Direction dir) override;
};

#endif // JBLOCK_H

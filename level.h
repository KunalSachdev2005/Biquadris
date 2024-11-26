#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include "block.h"
#include "player.h"

class Level {
protected:
    int level; // Level Number
    Player* player; // Pointer to associated player

public:
    Level(int levelNumber, Player* player); // Constructor
    virtual ~Level(); // Virtual destructor

    virtual Block* generateBlock() = 0; // Pure virtual function for generating a block
};

#endif // LEVEL_H

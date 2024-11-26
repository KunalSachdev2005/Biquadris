#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"
#include <memory>
#include <cstdlib>

class Level1 : public Level {
public:
    Level1(Player* player); // Constructor
    ~Level1() override; // Destructor

    Block* generateBlock() override; // Generate block for Level 1
};

#endif // LEVEL1_H

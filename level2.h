#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"

class Level2 : public Level {
public:
    Level2(Player* player); // Constructor
    ~Level2(); // Destructor

    Block* generateBlock() override; // Generates blocks with equal probability
};

#endif // LEVEL2_H

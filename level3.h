#ifndef LEVEL3_H
#define LEVEL3_H

#include "level.h"

class Level3 : public Level {
public:
    Level3(Player* player, int seed = 0); // Constructor
    ~Level3(); // Destructor

    Block* generateBlock() override; // Generates blocks with skewed probabilities for Level 3
};

#endif // LEVEL3_H

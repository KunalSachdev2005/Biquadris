#ifndef LEVEL4_H
#define LEVEL4_H

#include "level.h"

class Level4 : public Level {
public:
    Level4(Player* player); // Constructor
    ~Level4(); // Destructor

    Block* generateBlock() override; // Generates blocks with skewed probabilities for Level 3
};

#endif // LEVEL3_H

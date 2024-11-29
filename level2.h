#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"

class Level2 : public Level {
public:
    // Constructor
    Level2(Player* player, int seed = 0);

    // Destructor
    ~Level2();

    // Override the generateBlock method for Level2
    Block* generateBlock() override;
};

#endif // LEVEL2_H

#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"

class Level1 : public Level {
public:
    // Constructor: Initializes Level1 with the player and an optional seed
    Level1(Player* player, int seed = 0); 
    
    // Destructor
    ~Level1() override; 

    // Override the generateBlock method for Level1
    Block* generateBlock() override; 
};

#endif // LEVEL1_H

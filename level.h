#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <cstdlib>
#include <ctime>

#include "cell.h"
#include "block.h"
#include "board.h"
#include "player.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"

class Player;

class Level {
protected:
    int level;                                                      // Level Number
    Player* player;                                                 // Pointer to associated player

public:
    Level(int levelNumber, Player* player);                         // Constructor
    virtual ~Level();                                               // Virtual destructor
    int getLevel();
    virtual Block* generateBlock() = 0;                             // Pure virtual function for generating a block
    virtual void setSequenceMode(const std::string& filePath) {}    // Default: do nothing
    virtual void setRandomMode() {}                                 // Default: do nothing
};

#endif // LEVEL_H

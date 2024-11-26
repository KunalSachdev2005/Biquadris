#ifndef LEVEL0_H
#define LEVEL0_H

#include <fstream>
#include <string>
#include <vector>
#include "level.h"
#include "block.h"

class Level0 : public Level {
private:
    std::vector<std::string> blockSequence; // Sequence of block types
    int currentIndex; // Track current position in the sequence
    std::ifstream file; // File stream for reading block sequence

public:
    Level0(const std::string& fileName, Player* player); // Constructor - takes file name to read blocks from
    ~Level0() override; // Destructor

    Block* generateBlock() override; // override block generating method. Generate block based on file sequence
};

#endif // LEVEL0_H

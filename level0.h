#ifndef LEVEL0_H
#define LEVEL0_H

#include <fstream>
#include <string>
#include <vector>

#include "level.h"

// Forward declaration
class Player;

class Level0 : public Level {
private:
    // Member variables
    std::vector<std::string> blockSequence; // Sequence of block types
    int currentIndex;                       // Track current position in the sequence
    std::ifstream file;                     // File stream for reading block sequence

public:
    // Constructor
    Level0(const std::string& fileName, Player* player); 

    // Destructor
    ~Level0() override; 

    // Method to generate block based on file sequence
    Block* generateBlock() override; 
};

#endif // LEVEL0_H

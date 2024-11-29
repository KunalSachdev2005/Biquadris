#ifndef LEVEL4_H
#define LEVEL4_H

#include <fstream>
#include <queue>

#include "level.h"

// Forward declaration
class Block;

class Level4 : public Level {
private:
    // Member variables
    bool isRandom = true;                       // Determines if the level is random
    std::queue<std::string> sequenceQueue;      // Queue for sequence mode
    std::ifstream sequenceFile;                 // Input file for sequence mode

    // Helper methods
    Block* createBlockFromType(const std::string& type);    // Helper for sequence blocks
    Block* randomBlock();                                   // Helper for random blocks
    
public:
    // Constructor and Destructor
    Level4(Player* player, int seed = 0);
    ~Level4();

    // Public methods
    Block* generateBlock() override;                            // Generates blocks with skewed probabilities for Level 4
    void setSequenceMode(const std::string& filePath) override; // Switch to sequence mode using a given file path to load sequence
    void setRandomMode() override;                              // Switch to random mode
};

#endif // LEVEL4_H

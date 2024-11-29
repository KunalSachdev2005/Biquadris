#ifndef LEVEL3_H
#define LEVEL3_H

#include "level.h"
#include <fstream>
#include <queue>

class Level3 : public Level {
private:
    bool isRandom = true;                       // Determines if the level is random
    std::queue<std::string> sequenceQueue;      // Queue for sequence mode
    std::ifstream sequenceFile;                 // Input file stream for sequence mode

    // Helper method to create a Block from a specific type
    Block* createBlockFromType(const std::string& type);

    // Helper method to generate a random block
    Block* randomBlock();
    
public:
    // Constructor
    Level3(Player* player, int seed = 0);

    // Destructor
    ~Level3();

    Block* generateBlock() override;                            // Generates blocks with skewed probabilities for Level 3
    void setSequenceMode(const std::string& filePath) override; // Switch to sequence mode using a given file path to load sequence
    void setRandomMode() override;                              // Switch to random mode
};

#endif // LEVEL3_H

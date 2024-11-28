#ifndef LEVEL3_H
#define LEVEL3_H

#include "level.h"
#include <fstream>
#include <queue>

class Level3 : public Level {
private:
    bool isRandom = true; // Determines if the level is random
    std::queue<std::string> sequenceQueue; // Queue for sequence mode
    std::ifstream sequenceFile; // Input file for sequence mode

    Block* createBlockFromType(const std::string& type); // Helper for sequence blocks
    Block* randomBlock(); // Helper for random blocks
    
public:
    Level3(Player* player, int seed = 0); // Constructor
    ~Level3(); // Destructor

    Block* generateBlock() override; // Generates blocks with skewed probabilities for Level 3
    void setSequenceMode(const std::string& filePath) override; // Switch to sequence mode
    void setRandomMode() override; // Switch to random mode
};

#endif // LEVEL3_H

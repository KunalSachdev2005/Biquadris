#include "level1.h"

// Constructor for Level1
Level1::Level1(Player* player, int seed) : Level(1, player) {
    // Seed random number generator for generating block
    if (seed != 0) {
        std::srand(seed);
    } else {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }
}

// Destructor for Level1
Level1::~Level1() {}

// Generate block for Level 1
Block* Level1::generateBlock() {
    // Get the base cell for the new block    
    Cell* baseCell = player->getBoard()->at(20, 0);
    Block* block = nullptr;
    
    // Randomly select a block based on the probabilities
    int random = std::rand() % 12;

    if (random < 1) {
        // 1/12 probability for S-block
        block = new SBlock(level, baseCell);
    } else if (random < 2) {
        // 1/12 probability for Z-block
        block = new ZBlock(level, baseCell);
    } else if (random < 4) {
        // 2/12 probability for I-block
        block = new IBlock(level, baseCell);
    } else if (random < 6) {
        // 2/12 probability for J-block
        block = new JBlock(level, baseCell);
    } else if (random < 8) {
        // 2/12 probability for L-block
        block = new LBlock(level, baseCell);
    } else if (random < 10) {
        // 2/12 probability for O-block
        block = new OBlock(level, baseCell);
    } else {
        // 2/12 probability for T-block
        block = new TBlock(level, baseCell);
    }

    return block;
}

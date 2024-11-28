#include "level3.h"

// Constructor for Level 3
Level3::Level3(Player* player, int seed) : Level(3, player) {
    // Seed random number generator for block generation
    if (seed != 0) {
        std::srand(seed);
    } else {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }
}

// Destructor for Level 3
Level3::~Level3() {}

// Generate block for Level 3
Block* Level3::generateBlock() {
    // Get the base cell for the new block
    Cell* baseCell = player->getBoard()->at(20, 0); // Row 20, Column 0
    Block* block = nullptr;

    // Randomly select a block with skewed probabilities
    int random = std::rand() % 9; // Range [0, 8]

    if (random < 2) {         // 2/9 probability for SBlock
        block = new SBlock(level, baseCell);
    } else if (random < 4) {  // 2/9 probability for ZBlock
        block = new ZBlock(level, baseCell);
    } else if (random == 4) { // 1/9 probability for IBlock
        block = new IBlock(level, baseCell);
    } else if (random == 5) { // 1/9 probability for JBlock
        block = new JBlock(level, baseCell);
    } else if (random == 6) { // 1/9 probability for LBlock
        block = new LBlock(level, baseCell);
    } else if (random == 7) { // 1/9 probability for OBlock
        block = new OBlock(level, baseCell);
    } else if (random == 8) { // 1/9 probability for TBlock
        block = new TBlock(level, baseCell);
    }

    // All blocks in Level 3 are heavy
    block->setHeavy(true); // need to implement the if possible part. read biquadris pdf for level 3
    block->setWeight(1);

    return block;
}

#include "level2.h"

// Constructor for Level 2
Level2::Level2(Player* player) : Level(2, player) {
    // Seed random number generator for block generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// Destructor for Level 2
Level2::~Level2() {}

// Generate block for Level 2
Block* Level2::generateBlock() {
    // Get the base cell for the new block
    Cell* baseCell = player->getBoard()->at(20, 0); // Row 20, Column 0
    Block* block = nullptr;

    // Randomly select a block with equal probability
    int random = std::rand() % 7; // 7 types of blocks

    switch (random) {
        case 0:
            block = new IBlock(level, baseCell);
            break;
        case 1:
            block = new JBlock(level, baseCell);
            break;
        case 2:
            block = new LBlock(level, baseCell);
            break;
        case 3:
            block = new OBlock(level, baseCell);
            break;
        case 4:
            block = new SBlock(level, baseCell);
            break;
        case 5:
            block = new ZBlock(level, baseCell);
            break;
        case 6:
            block = new TBlock(level, baseCell);
            break;
    }

    return block;
}

#include "level0.h"

// Constructor for Level0
Level0::Level0(const std::string& fileName, Player* player) 
    : Level(0, player), currentIndex(0) {
    file.open(fileName);
    if (!file) {
        throw std::runtime_error("Unable to open script file: " + fileName);
    }

    // Reading block sequence from file
    std::string blockType;
    while (file >> blockType) {
        blockSequence.push_back(blockType);
    }
    file.close();
}

// Destructor for Level0
Level0::~Level0() {
    if (file.is_open()) {
        file.close();
    }
}

// Override generateBlock method
Block* Level0::generateBlock() {
    if (blockSequence.empty()) {
        throw std::runtime_error("No blocks available in sequence.");
    }
    
    std::string blockType = blockSequence[currentIndex];
    currentIndex = (currentIndex + 1) % blockSequence.size(); // Loop back to the start once blocks are over

    Cell* baseCell = player->getBoard()->at(20, 0); // Gets the base cell for the block

    if (blockType == "I") return new IBlock(level, baseCell);
    if (blockType == "J") return new JBlock(level, baseCell);
    if (blockType == "L") return new LBlock(level, baseCell);
    if (blockType == "O") return new OBlock(level, baseCell);
    if (blockType == "S") return new SBlock(level, baseCell);
    if (blockType == "Z") return new ZBlock(level, baseCell);
    if (blockType == "T") return new TBlock(level, baseCell);
    
    throw std::runtime_error("Unknown block type: " + blockType);
}

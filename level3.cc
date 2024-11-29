#include "level3.h"

const int HEAVY_WEIGHT = 1;

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
Level3::~Level3() {
    if (sequenceFile.is_open()) {
        sequenceFile.close();
    }
}

void Level3::setSequenceMode(const std::string& filePath) {
    isRandom = false;

    while (!sequenceQueue.empty()) {
    sequenceQueue.pop();
    }

    if (sequenceFile.is_open()) {
        sequenceFile.close();
    }
    sequenceFile.open(filePath);
    if (!sequenceFile) {
        throw std::runtime_error("Failed to open sequence file: " + filePath);
    }
}

void Level3::setRandomMode() {
    isRandom = true;
    if (sequenceFile.is_open()) {
        sequenceFile.close();
    }
}

// Generate block for Level 3
Block* Level3::generateBlock() {
    if (isRandom) {
        return randomBlock(); // Generate a random block
    }
    else {
        // If sequence mode is active, load blocks from the sequence file
        if (sequenceQueue.empty() && sequenceFile.is_open()) {
            std::string blockType;
            // Read all block types from the file into the sequence queue
            while (sequenceFile >> blockType) {
                sequenceQueue.push(blockType);
            }
            // Reset the file stream for future reuse
            sequenceFile.clear();
            sequenceFile.seekg(0);
        }

        // If there are blocks in the queue, use the next block
        if (!sequenceQueue.empty()) {
            std::string blockType = sequenceQueue.front();
            sequenceQueue.pop();
            return createBlockFromType(blockType);
        }

        // If the sequence fails, fallback to random block generation
        return randomBlock();
    }
    
}

// Helper to create block from type
Block* Level3::createBlockFromType(const std::string& type) {
    Cell* baseCell = player->getBoard()->at(20, 0);
    
    if (type == "I") return new IBlock(level, baseCell);
    if (type == "J") return new JBlock(level, baseCell);
    if (type == "L") return new LBlock(level, baseCell);
    if (type == "O") return new OBlock(level, baseCell);
    if (type == "S") return new SBlock(level, baseCell);
    if (type == "Z") return new ZBlock(level, baseCell);
    if (type == "T") return new TBlock(level, baseCell);

    // Handle invalid block type in sequence
    throw std::runtime_error("Invalid block type in sequence: " + type);
}

// Helper to generate random block (with skewed probabilities)
Block* Level3::randomBlock() {
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
    block->setHeavy(true);
    block->setWeight(HEAVY_WEIGHT);

    return block;
}

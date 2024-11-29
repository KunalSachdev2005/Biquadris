#include "player.h"
#include "specialaction.h"

// Constructor
Player::Player(std::string playerName) 
    : name(playerName), board(), score(), level(nullptr), blocksSinceClear(0), isTurn(false), gameOver(false) {
    // Default level might be set elsewhere or through a setter
}

// Getters
std::string Player::getName() const { return name; }
Board* Player::getBoard() { return &board; }
Score& Player::getScore() { return score; }
std::shared_ptr<Level> Player::getLevel() const {
    return std::make_shared<Level>(*level);  // Return a shared pointer by copying the level
}
int Player::getBlocksSinceClear() const { return blocksSinceClear; }
bool Player::getIsTurn() const { return isTurn; }

// Setters
void Player::setName(const std::string& newName) { name = newName; }
void Player::setLevel(std::shared_ptr<Level> newLevel) { 
    level = std::move(newLevel);
}
void Player::setIsTurn(bool turn) { isTurn = turn; }

// Game-related methods
void Player::incrementTurn() { ++blocksSinceClear; }

void Player::resetTurn() {
    blocksSinceClear = 0;
    isTurn = false;
}

void Player::setBlocksSinceClear(int i) {
    blocksSinceClear = i;
}

Block* Player::generateNextBlock() {
    if (level) {
        return level->generateBlock();
    }
    return nullptr;  // Or handle error appropriately
}

bool Player::isGameOver() { return gameOver; }

void Player::setGameOver() { gameOver = true;}

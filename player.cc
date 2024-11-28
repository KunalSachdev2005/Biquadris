#include "player.h"
#include "specialaction.h"

// Constructor
Player::Player(std::string playerName) 
    : name(playerName), board(), score(), highScore(), level(nullptr), turns(0), isTurn(false) {
    // Default level might be set elsewhere or through a setter
}

// Destructor
Player::~Player() {
    delete level;  // Clean up dynamically allocated level
}

// Getters
std::string Player::getName() const { return name; }
Board* Player::getBoard() { return &board; }
Score& Player::getScore() { return score; }
Score& Player::getHighScore() { return highScore; }
Level* Player::getLevel() const { return level; }
int Player::getTurns() const { return turns; }
bool Player::getIsTurn() const { return isTurn; }

// Setters
void Player::setName(const std::string& newName) { name = newName; }
void Player::setLevel(Level* newLevel) { 
    delete level;  // Clean up existing level
    level = newLevel; 
}
void Player::setIsTurn(bool turn) { isTurn = turn; }

// Game-related methods
void Player::incrementTurns() { ++turns; }

void Player::updateHighScore() {
    int currentScore = score.getScore();
    int currentHighScore = highScore.getScore();
    if (currentScore > currentHighScore) {
        highScore.resetScore();
        highScore.addScore(currentScore);
    }
}

void Player::resetTurn() {
    turns = 0;
    isTurn = false;
}

Block* Player::generateNextBlock() {
    if (level) {
        return level->generateBlock();
    }
    return nullptr;  // Or handle error appropriately
}



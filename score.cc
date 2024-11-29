#include "score.h"

// Constructor
Score::Score() : score(0), highScore(0) {}

// Add points to the score
void Score::addScore(int value) {
    score += value;
}

// Get current score
int Score::getScore() const {
    return score;
}

int Score::getHighScore() const {
    return highScore;
}
void Score::setHighScore(int score) {
    highScore = score;
}

// Reset the currrent score to 0
void Score::resetScore() {
    score = 0;
}

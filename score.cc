#include "score.h"

const int INIT_SCORE = 0;
const int INIT_HIGHSCORE = 0;

// Constructor
Score::Score() : score(INIT_SCORE), highScore(INIT_HIGHSCORE) {}

// Add points to the score
void Score::addScore(int value) {
    score += value;
}

// Get current score
int Score::getScore() const {
    return score;
}

// Get high score
int Score::getHighScore() const {
    return highScore;
}

// Set high score
void Score::setHighScore(int score) {
    highScore = score;
}

// Reset the current score to 0
void Score::resetScore() {
    score = INIT_SCORE;
}

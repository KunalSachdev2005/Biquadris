#ifndef SCORE_H
#define SCORE_H

class Score {
    int score;

public:
    // Constructor
    Score();

    // Methods
    void addScore(int value); // Add points to current score
    int getScore() const; // Get current score
    void resetScore(); // Reset the current score to 0
};

#endif

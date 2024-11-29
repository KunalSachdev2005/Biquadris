#ifndef SCORE_H
#define SCORE_H

class Score {
    int score;
    int highScore;

public:
    // Constructor
    Score();

    // Methods
    void addScore(int value);       // Add points to current score
    int getScore() const;           // Get current score
    int getHighScore() const;       // Get high score
    void setHighScore(int score);   // Set high score
    void resetScore();              // Reset the current score to 0
};

#endif

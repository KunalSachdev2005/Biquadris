#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "board.h"
#include "score.h"
#include "level.h"

class Level;

class Player {
private:
    std::string name;
    Board board;
    Score score;
    Score highScore;
    Level* level;
    int turns;
    bool isTurn;

public:
    // Constructors
    Player(std::string playerName = "Player");
    ~Player();

    // Getters
    std::string getName() const;
    Board* getBoard();
    Score& getScore();
    Score& getHighScore();
    Level* getLevel() const;
    int getTurns() const;
    bool getIsTurn() const;

    // Setters
    void setName(const std::string& newName);
    void setLevel(Level* newLevel);
    void setIsTurn(bool turn);

    // Game-related methods
    void incrementTurns();
    void updateHighScore();
    void resetTurn();
    Block* generateNextBlock();
    void applySpecialAction(int actionType);
};

#endif // PLAYER_H

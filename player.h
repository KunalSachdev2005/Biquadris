#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "board.h"
#include "score.h"
#include "level.h"

class SpecialAction;

class Level;

class Player {
private:
    std::string name;
    Board board;
    Score score;
    Level* level;
    int blocksSinceClear;
    bool isTurn;
    bool gameOver;

public:
    // Constructors
    Player(std::string playerName = "Player");
    ~Player();

    // Getters
    std::string getName() const;
    Board* getBoard();
    Score& getScore();
    Level* getLevel() const;
    int getBlocksSinceClear() const;
    bool getIsTurn() const;
    bool isGameOver();

    // Setters
    void setName(const std::string& newName);
    void setLevel(Level* newLevel);
    void setIsTurn(bool turn);
    void setGameOver();

    // Game-related methods
    void incrementTurn();
    void resetTurn();
    Block* generateNextBlock();
    void applySpecialAction(SpecialAction* action);

    void setBlocksSinceClear(int i);
};

#endif // PLAYER_H

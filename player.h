#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>

#include "board.h"
#include "score.h"
#include "level.h"

// Forward Declaration
class SpecialAction;
class Level;

class Player {
private:
    std::string name;          // Player's name
    Board board;               // The player's game board
    Score score;               // The player's score
    std::shared_ptr<Level> level;              // Pointer to the current level
    int blocksSinceClear;      // Blocks cleared since last reset
    bool isTurn;               // Whether it is the player's turn
    bool gameOver;             // Whether the game is over for this player

public:
    // Constructors and Destructor
    Player(std::string playerName = "Player");

    // Getters (Accessors)
    std::string getName() const;
    Board* getBoard();
    Score& getScore();
    std::shared_ptr<Level> getLevel() const;
    int getBlocksSinceClear() const;
    bool getIsTurn() const;
    bool isGameOver();

    // Setters (Mutators)
    void setName(const std::string& newName);
    void setLevel(std::unique_ptr<Level> newLevel);
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

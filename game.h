#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "commandinterpreter.h"  // Assuming you'll create this
#include "textdisplay.h"  // Assuming you'll create this
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

class Game {
private:
    Player player1;
    Player player2;
    Player* currentPlayer;
    bool gameOver;
    CommandInterpreter commandInterpreter;
    TextDisplay textDisplay;
    std::string scriptFile1;
    std::string scriptFile2;
    int randomSeed;

public:
    // Constructors
    Game(const std::string& player1Name, const std::string& player2Name, int startLevel, const std::string& scriptFile1 = "sequence1.txt", 
        const std::string& scriptFile2 = "sequence2.txt", int randomSeed = 0);
    
    // Game management methods
    void initialize(int player1Level, int player2Level);
    void start();
    void switchTurns();
    void processCommand(const std::string& command);
    void checkGameState();
    void applySpecialAction();
    void handleGameOver();

    Type charToType(char ch);
    
    // Getters
    Player* getCurrentPlayer();
    Player* getOpponentPlayer();
    Player* getPlayer1();
    Player* getPlayer2();
    bool isGameOver() const;
    
    // Display methods
    void updateDisplay();
    void showScores();
    void printInstructions();

    void levelUp(Player* player);
    void levelDown(Player* player);

    void applySpecialAction(SpecialAction* action);
};

#endif // GAME_H

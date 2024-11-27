#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "commandinterpreter.h"  // Assuming you'll create this
#include "textdisplay.h"  // Assuming you'll create this

class Game {
private:
    Player player1;
    Player player2;
    Player* currentPlayer;
    bool gameOver;
    CommandInterpreter commandInterpreter;
    TextDisplay textDisplay;

public:
    // Constructors
    Game(const std::string& player1Name = "Player 1", 
         const std::string& player2Name = "Player 2");
    
    // Game management methods
    void initialize();
    void start();
    void switchTurns();
    void processCommand(const std::string& command);
    void checkGameState();
    void applySpecialAction();
    void handleGameOver();
    
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
};

#endif // GAME_H

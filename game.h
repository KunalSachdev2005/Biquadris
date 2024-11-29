#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "commandinterpreter.h"  
#include "textdisplay.h"  
#include "graphicdisplay.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

class GraphicDisplay;

class Game {
private:
    Player player1;
    Player player2;
    Player* currentPlayer;
    CommandInterpreter commandInterpreter;
    TextDisplay textDisplay;
    GraphicDisplay* graphicDisplay;
    std::string scriptFile1;
    std::string scriptFile2;
    int randomSeed;
    int startLevel;
    bool textMode;

public:
    // Constructors
    Game(const std::string& player1Name, const std::string& player2Name, int startLevel, const std::string& scriptFile1 = "sequence1.txt", 
        const std::string& scriptFile2 = "sequence2.txt", int randomSeed = 0, bool textMode = false, int player1HighScore=0, int player2HighScore=0);
    
    // Game management methods
    void initialize(int player1Level, int player2Level, int player1HighScore, int player2HighScore);
    void start();
    void switchTurns();
    void processCommand(const std::string& command);
    void checkGameState();
    void applySpecialAction();
    void handleGameOver();

    Type charToType(char ch);

    void dropSpecialBlock(Player* p);
    
    // Getters
    Player* getCurrentPlayer();
    Player* getOpponentPlayer();
    Player* getPlayer1();
    Player* getPlayer2();
    int getStartLevel() const;
    int getSeed() const;
    bool inTextMode() const;

    
    // Display methods
    void updateDisplay();
    void showScores();
    void printInstructions();
    void printGameResults() const;

    void levelUp(Player* player);
    void levelDown(Player* player);

    void applySpecialAction(SpecialAction* action);
    ~Game();
};

#endif // GAME_H

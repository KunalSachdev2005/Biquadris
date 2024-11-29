#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "game.h"

// Forward declaration
class Game;
class Player;
class Cell;

class TextDisplay {
private:
    // Pointer to the Game object
    Game* game;

    // Private methods related to displaying information
    void printSideBySideBoards(Player* player1, Player* player2);
    void printNextBlocks(Player* player1, Player* player2);
    void printCell(Cell* cell);
    char getBlockTypeChar(Block* block);

public:
    // Constructor
    TextDisplay(Game* game);

    // Public method to update the display
    void update();
};

#endif // TEXTDISPLAY_H

#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "player.h"
#include "block.h"
#include "cell.h"

class Game;

class TextDisplay {
private:
    Game* game;

    void printSideBySideBoards(Player* player1, Player* player2);
    void printNextBlocks(Player* player1, Player* player2);
    void printCell(Cell* cell);
    char getBlockTypeChar(Block* block);

public:
    TextDisplay(Game* game);
    void update();
};

#endif // TEXTDISPLAY_H
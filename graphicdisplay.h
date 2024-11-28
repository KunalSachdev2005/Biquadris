#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "game.h"
#include "xwindow.h"

class GraphicDisplay {
private:
    Game* game;
    Xwindow* window;

    // Drawing configuration
    const int BOARD_START_X = 50;
    const int BOARD_START_Y = 50;
    const int CELL_SIZE = 30;
    const int BOARD_WIDTH = 11;
    const int BOARD_HEIGHT = 18;

    // Helper methods for drawing
    void drawCell(int x, int y, Block* block);
    void drawBoard(Player* player, int startX, int startY);
    void drawScoreAndLevel(Player* player, int startX, int startY);
    Xwindow::Color getBlockColor(Type blockType) const;

public:
    GraphicDisplay(Game* game);
    ~GraphicDisplay();

    void update();
};

#endif // GRAPHICDISPLAY_H

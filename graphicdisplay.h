#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "xwindow.h"
#include "game.h"
#include <vector>
#include <string>

class GraphicDisplay {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 1000;
    const int CELL_SIZE = 30;
    const int BOARD_WIDTH = CELL_SIZE * 11;
    const int BOARD_HEIGHT = CELL_SIZE * 18;
    const int BOARD_OFFSET_X = 50;
    const int BOARD1_OFFSET_Y = 150;
    const int BOARD2_OFFSET_Y = 150;
    const int TEXT_MARGIN = 10;

    const int EMPTY = XWindow::Color::Black;
    const int I_BLOCK = XWindow::Color::Cyan;
    const int J_BLOCK = XWindow::Color::Blue;
    const int L_BLOCK = XWindow::Color::Orange;
    const int O_BLOCK = XWindow::Color::Yellow;
    const int S_BLOCK = XWindow::Color::Green;
    const int Z_BLOCK = XWindow::Color::Red;
    const int T_BLOCK = XWindow::Color::Magenta;
    const int SP_BLOCK = XWindow::Color::White;

    Game* game;
    XWindow* window;

    std::vector<std::vector<int>> previousPlayer1Board;
    std::vector<std::vector<int>> previousPlayer2Board;

    int previousPlayer1Level;
    int previousPlayer1Score;
    int previousPlayer1HighScore;
    int previousPlayer2Level;
    int previousPlayer2Score;
    int previousPlayer2HighScore;

    void drawStaticGrid();
    void drawGridLines(int offsetX, int offsetY);
    int getColorForBlockType(Type blockType);
    void drawBoard(Player* player, int offsetX, int offsetY, std::vector<std::vector<int>>& previousBoard);
    void drawTextInfo(Player* player1, Player* player2);
    void drawNextBlock(Player* player, int offsetX, int offsetY);

public:
    GraphicDisplay(Game* game);
    ~GraphicDisplay();

    void update();
};

#endif

#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "xwindow.h"
#include "game.h"
#include <vector>
#include <unordered_map>

class GraphicDisplay {
private:
    XWindow* window;
    Game* game;

    // Screen layout constants
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 1000;
    static constexpr int BOARD_WIDTH = 330;
    static constexpr int BOARD_HEIGHT = 540;
    static constexpr int CELL_SIZE = 30;
    static constexpr int BOARD_OFFSET_X = 50;
    static constexpr int BOARD1_OFFSET_Y = 100;
    static constexpr int BOARD2_OFFSET_Y = 100;
    static constexpr int TEXT_MARGIN = 20;

    // Color mapping
    enum BlockColors {
        EMPTY = XWindow::Color::White,
        I_BLOCK = XWindow::Color::Cyan,
        J_BLOCK = XWindow::Color::Blue,
        L_BLOCK = XWindow::Color::Orange,
        O_BLOCK = XWindow::Color::Yellow,
        S_BLOCK = XWindow::Color::Green,
        Z_BLOCK = XWindow::Color::Red,
        T_BLOCK = XWindow::Color::Magenta,
        SP_BLOCK = XWindow::Color::Brown
    };

    // Track previous state to minimize redrawing
    std::vector<std::vector<int>> previousPlayer1Board;
    std::vector<std::vector<int>> previousPlayer2Board;
    int previousPlayer1Level = -1;
    int previousPlayer1Score = -1;
    int previousPlayer1HighScore = -1;
    int previousPlayer2Level = -1;
    int previousPlayer2Score = -1;
    int previousPlayer2HighScore = -1;

    // Helper methods
    int getColorForBlockType(Type blockType);
    void drawBoard(Player* player, int offsetX, int offsetY, std::vector<std::vector<int>>& previousBoard);
    void drawTextInfo(Player* player1, Player* player2);
    void drawNextBlock(Player* player, int offsetX, int offsetY);
    void drawBoardWithGrid(Player* player, int offsetX, int offsetY, std::vector<std::vector<int>>& previousBoard);
    void drawNextBlockSection(Player* player, int offsetX, int offsetY);

public:
    GraphicDisplay(Game* game);
    ~GraphicDisplay();

    void update();
};

#endif // GRAPHICDISPLAY_H

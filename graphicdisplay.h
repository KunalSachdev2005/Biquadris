#ifndef GRAPHIC_DISPLAY_H
#define GRAPHIC_DISPLAY_H

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
    static constexpr int WINDOW_HEIGHT = 600;
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

public:
    GraphicDisplay(Game* game);
    ~GraphicDisplay();

    void update();
};

#endif // GRAPHIC_DISPLAY_H

// GraphicDisplay.cpp implementation
GraphicDisplay::GraphicDisplay(Game* game) : game(game) {
    window = new XWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Initialize previous board states
    previousPlayer1Board.resize(18, std::vector<int>(11, EMPTY));
    previousPlayer2Board.resize(18, std::vector<int>(11, EMPTY));
}

GraphicDisplay::~GraphicDisplay() {
    delete window;
}

int GraphicDisplay::getColorForBlockType(Type blockType) {
    switch(blockType) {
        case Type::I: return I_BLOCK;
        case Type::J: return J_BLOCK;
        case Type::L: return L_BLOCK;
        case Type::O: return O_BLOCK;
        case Type::S: return S_BLOCK;
        case Type::Z: return Z_BLOCK;
        case Type::T: return T_BLOCK;
        case Type::SP: return SP_BLOCK;
        default: return EMPTY;
    }
}

void GraphicDisplay::drawBoard(Player* player, int offsetX, int offsetY, std::vector<std::vector<int>>& previousBoard) {
    for (int r = 0; r < 18; ++r) {
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player->getBoard()->at(r, c);
            int currentColor = EMPTY;

            if (cell->isBlind()) {
                currentColor = XWindow::Color::Black;
            } else if (cell->isOccupied()) {
                Block* block = cell->getBlock();
                currentColor = getColorForBlockType(block->getType());
            }

            // Only redraw if color has changed
            if (currentColor != previousBoard[r][c]) {
                window->fillRectangle(
                    offsetX + c * CELL_SIZE, 
                    offsetY + r * CELL_SIZE, 
                    CELL_SIZE, 
                    CELL_SIZE, 
                    currentColor
                );
                previousBoard[r][c] = currentColor;
            }
        }
    }
}

void GraphicDisplay::drawTextInfo(Player* player1, Player* player2) {
    // Player 1 Info
    if (player1->getLevel()->getLevel() != previousPlayer1Level ||
        player1->getScore().getScore() != previousPlayer1Score ||
        player1->getScore().getHighScore() != previousPlayer1HighScore) {
        
        // Clear previous text area
        window->fillRectangle(0, 0, WINDOW_WIDTH / 2, 100, XWindow::Color::White);
        
        std::string levelStr = "Level: " + std::to_string(player1->getLevel()->getLevel());
        std::string scoreStr = "Score: " + std::to_string(player1->getScore().getScore());
        std::string highScoreStr = "High Score: " + std::to_string(player1->getScore().getHighScore());
        
        window->drawString(TEXT_MARGIN, 30, levelStr);
        window->drawString(TEXT_MARGIN, 50, scoreStr);
        window->drawString(TEXT_MARGIN, 70, highScoreStr);

        // Update previous values
        previousPlayer1Level = player1->getLevel()->getLevel();
        previousPlayer1Score = player1->getScore().getScore();
        previousPlayer1HighScore = player1->getScore().getHighScore();
    }

    // Player 2 Info (similar to Player 1)
    if (player2->getLevel()->getLevel() != previousPlayer2Level ||
        player2->getScore().getScore() != previousPlayer2Score ||
        player2->getScore().getHighScore() != previousPlayer2HighScore) {
        
        // Clear previous text area
        window->fillRectangle(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, 100, XWindow::Color::White);
        
        std::string levelStr = "Level: " + std::to_string(player2->getLevel()->getLevel());
        std::string scoreStr = "Score: " + std::to_string(player2->getScore().getScore());
        std::string highScoreStr = "High Score: " + std::to_string(player2->getScore().getHighScore());
        
        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 30, levelStr);
        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 50, scoreStr);
        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 70, highScoreStr);

        // Update previous values
        previousPlayer2Level = player2->getLevel()->getLevel();
        previousPlayer2Score = player2->getScore().getScore();
        previousPlayer2HighScore = player2->getScore().getHighScore();
    }
}

void GraphicDisplay::drawNextBlock(Player* player, int offsetX, int offsetY) {
    Block* nextBlock = player->getBoard()->getNextBlock();
    if (nextBlock) {
        int blockColor = getColorForBlockType(nextBlock->getType());
        
        // Draw next block preview (simplified representation)
        for (int r = 21; r < 24; ++r) {
            for (int c = 0; c < 11; ++c) {
                Cell* cell = player->getBoard()->at(r, c);
                
                if (cell->isOccupied()) {
                    window->fillRectangle(
                        offsetX + c * CELL_SIZE, 
                        offsetY + (r - 21) * CELL_SIZE, 
                        CELL_SIZE, 
                        CELL_SIZE, 
                        blockColor
                    );
                }
            }
        }
    }
}

void GraphicDisplay::update() {
    Player* player1 = game->getPlayer1();
    Player* player2 = game->getPlayer2();

    // Draw board backgrounds
    window->fillRectangle(BOARD_OFFSET_X, BOARD1_OFFSET_Y, BOARD_WIDTH, BOARD_HEIGHT, XWindow::Color::White);
    window->fillRectangle(WINDOW_WIDTH - BOARD_OFFSET_X - BOARD_WIDTH, BOARD2_OFFSET_Y, BOARD_WIDTH, BOARD_HEIGHT, XWindow::Color::White);

    // Draw boards with differential rendering
    drawBoard(player1, BOARD_OFFSET_X, BOARD1_OFFSET_Y, previousPlayer1Board);
    drawBoard(player2, WINDOW_WIDTH - BOARD_OFFSET_X - BOARD_WIDTH, BOARD2_OFFSET_Y, previousPlayer2Board);

    // Draw text information
    drawTextInfo(player1, player2);

    // Draw next block previews
    drawNextBlock(player1, BOARD_OFFSET_X, BOARD1_OFFSET_Y + BOARD_HEIGHT + 20);
    drawNextBlock(player2, WINDOW_WIDTH - BOARD_OFFSET_X - BOARD_WIDTH, BOARD2_OFFSET_Y + BOARD_HEIGHT + 20);
}
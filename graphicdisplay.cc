#include "graphicdisplay.h"
#include <sstream>
#include <iomanip>

GraphicDisplay::GraphicDisplay(Game* game) : game(game), window(new Xwindow()) {}

GraphicDisplay::~GraphicDisplay() {
    delete window;
}

Xwindow::Color GraphicDisplay::getBlockColor(Type blockType) const {
    switch (blockType) {
        case Type::I: return Xwindow::Cyan;
        case Type::J: return Xwindow::Blue;
        case Type::L: return Xwindow::Orange;
        case Type::O: return Xwindow::Yellow;
        case Type::S: return Xwindow::Green;
        case Type::T: return Xwindow::Magenta;
        case Type::Z: return Xwindow::Red;
        default: return Xwindow::White;
    }
}

void GraphicDisplay::drawCell(int x, int y, Block* block) {
    if (!block) {
        window->fillRectangle(x, y, CELL_SIZE, CELL_SIZE, Xwindow::White);
        return;
    }
    
    Xwindow::Color color = getBlockColor(block->getType());
    window->fillRectangle(x, y, CELL_SIZE, CELL_SIZE, color);
    window->drawLine(x, y, x + CELL_SIZE, y, Xwindow::Black);
    window->drawLine(x + CELL_SIZE, y, x + CELL_SIZE, y + CELL_SIZE, Xwindow::Black);
}

void GraphicDisplay::drawBoard(Player* player, int startX, int startY) {
    Board* board = player->getBoard();
    
    // Draw board background
    window->fillRectangle(startX, startY, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE, Xwindow::White);
    
    // Draw cells
    for (int r = 0; r < BOARD_HEIGHT; ++r) {
        for (int c = 0; c < BOARD_WIDTH; ++c) {
            Cell* cell = board->at(r, c);
            drawCell(startX + c * CELL_SIZE, startY + r * CELL_SIZE, cell->getBlock());
        }
    }
}

void GraphicDisplay::drawScoreAndLevel(Player* player, int startX, int startY) {
    std::ostringstream levelStr, scoreStr, highScoreStr;
    
    levelStr << "Level: " << player->getLevel()->getLevel();
    scoreStr << "Score: " << player->getScore().getScore();
    highScoreStr << "Hi Score: " << player->getHighScore().getScore();
    
    window->drawString(startX, startY - 10, player->getName());
    window->drawString(startX, startY + 10, levelStr.str());
    window->drawString(startX, startY + 30, scoreStr.str());
    window->drawString(startX, startY + 50, highScoreStr.str());
}

void GraphicDisplay::update() {
    // Clear entire window
    window->fillRectangle(0, 0, window->getWidth(), window->getHeight(), Xwindow::White);

    Player* player1 = game->getPlayer1();
    Player* player2 = game->getPlayer2();

    // Draw first player's board and stats
    drawBoard(player1, BOARD_START_X, BOARD_START_Y);
    drawScoreAndLevel(player1, BOARD_START_X, BOARD_START_Y - 50);

    // Draw second player's board and stats
    drawBoard(player2, BOARD_START_X + BOARD_WIDTH * CELL_SIZE + 100, BOARD_START_Y);
    drawScoreAndLevel(player2, BOARD_START_X + BOARD_WIDTH * CELL_SIZE + 100, BOARD_START_Y - 50);

    // Optional: Draw a visual separator between boards
    window->drawLine(
        BOARD_START_X + BOARD_WIDTH * CELL_SIZE + 50, 
        BOARD_START_Y, 
        BOARD_START_X + BOARD_WIDTH * CELL_SIZE + 50, 
        BOARD_START_Y + BOARD_HEIGHT * CELL_SIZE
    );
}

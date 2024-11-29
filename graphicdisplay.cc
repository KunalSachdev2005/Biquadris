#include "graphicdisplay.h"

// Constructor
GraphicDisplay::GraphicDisplay(Game* game) : game(game) {
    window = new XWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Initialize previous board states
    previousPlayer1Board.resize(18, std::vector<int>(11, EMPTY));
    previousPlayer2Board.resize(18, std::vector<int>(11, EMPTY));

    // Initialize previous text info
    previousPlayer1Level = -1;
    previousPlayer1Score = -1;
    previousPlayer1HighScore = -1;
    previousPlayer2Level = -1;
    previousPlayer2Score = -1;
    previousPlayer2HighScore = -1;

    // Draw static elements (grid)
    drawStaticGrid();
}

// Destructor
GraphicDisplay::~GraphicDisplay() {
    delete window;
}

// Draw static grid once
void GraphicDisplay::drawStaticGrid() {
    drawGridLines(BOARD_OFFSET_X, BOARD1_OFFSET_Y);
    drawGridLines(WINDOW_WIDTH - BOARD_OFFSET_X - BOARD_WIDTH, BOARD2_OFFSET_Y);
}

// Draw grid lines
void GraphicDisplay::drawGridLines(int offsetX, int offsetY) {
    for (int r = 0; r <= 18; ++r) {
        window->fillRectangle(
            offsetX, 
            offsetY + r * CELL_SIZE, 
            BOARD_WIDTH, 
            1, 
            XWindow::Color::White
        );
    }
    for (int c = 0; c <= 11; ++c) {
        window->fillRectangle(
            offsetX + c * CELL_SIZE, 
            offsetY, 
            1, 
            BOARD_HEIGHT, 
            XWindow::Color::White
        );
    }
}

// Map block type to color
int GraphicDisplay::getColorForBlockType(Type blockType) {
    switch (blockType) {
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

// Draw board using dirty rectangles
void GraphicDisplay::drawBoard(Player* player, int offsetX, int offsetY, std::vector<std::vector<int>>& previousBoard) {
    for (int r = 0; r < 18; ++r) {
        for (int c = 0; c < 11; ++c) {
            Cell* cell = player->getBoard()->at(r, c);
            int currentColor = EMPTY;

            if (cell->isBlind()) {
                currentColor = XWindow::Color::Black;
            } else if (cell->isOccupied()) {
                Block* block = cell->getBlock();
                if (block) {
                    currentColor = getColorForBlockType(block->getType());
                }
            }

            if (currentColor != previousBoard[r][c]) {
                window->fillRectangle(
                    offsetX + c * CELL_SIZE + 1, 
                    offsetY + r * CELL_SIZE + 1, 
                    CELL_SIZE - 2, 
                    CELL_SIZE - 2, 
                    currentColor
                );
                previousBoard[r][c] = currentColor;
            }
        }
    }
}

// Draw text information
void GraphicDisplay::drawTextInfo(Player* player1, Player* player2) {
    if (player1->getLevel()->getLevel() != previousPlayer1Level ||
        player1->getScore().getScore() != previousPlayer1Score ||
        player1->getScore().getHighScore() != previousPlayer1HighScore) {

        window->fillRectangle(0, 0, WINDOW_WIDTH / 2, 100, XWindow::Color::Black);

        window->drawString(TEXT_MARGIN, 30, "Level: " + std::to_string(player1->getLevel()->getLevel()), XWindow::Color::White);
        window->drawString(TEXT_MARGIN, 50, "Score: " + std::to_string(player1->getScore().getScore()), XWindow::Color::White);
        window->drawString(TEXT_MARGIN, 70, "High Score: " + std::to_string(player1->getScore().getHighScore()), XWindow::Color::White);

        previousPlayer1Level = player1->getLevel()->getLevel();
        previousPlayer1Score = player1->getScore().getScore();
        previousPlayer1HighScore = player1->getScore().getHighScore();
    }

    if (player2->getLevel()->getLevel() != previousPlayer2Level ||
        player2->getScore().getScore() != previousPlayer2Score ||
        player2->getScore().getHighScore() != previousPlayer2HighScore) {

        window->fillRectangle(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, 100, XWindow::Color::Black);

        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 30, "Level: " + std::to_string(player2->getLevel()->getLevel()), XWindow::Color::White);
        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 50, "Score: " + std::to_string(player2->getScore().getScore()), XWindow::Color::White);
        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 70, "High Score: " + std::to_string(player2->getScore().getHighScore()), XWindow::Color::White);

        previousPlayer2Level = player2->getLevel()->getLevel();
        previousPlayer2Score = player2->getScore().getScore();
        previousPlayer2HighScore = player2->getScore().getHighScore();
    }
}

// Draw next block
void GraphicDisplay::drawNextBlock(Player* player, int offsetX, int offsetY) {
    window->fillRectangle(offsetX, offsetY, 11 * CELL_SIZE, 3 * CELL_SIZE, XWindow::Color::Black);

    Block* nextBlock = player->getBoard()->getNextBlock();
    if (nextBlock) {
        int blockColor = getColorForBlockType(nextBlock->getType());
        for (const auto& cell : nextBlock->getCells()) {
            window->fillRectangle(
                offsetX + cell.x * CELL_SIZE + 1, 
                offsetY + cell.y * CELL_SIZE + 1, 
                CELL_SIZE - 2, 
                CELL_SIZE - 2, 
                blockColor
            );
        }
    }
}

// Update display
void GraphicDisplay::update() {
    Player* player1 = game->getPlayer1();
    Player* player2 = game->getPlayer2();

    drawBoard(player1, BOARD_OFFSET_X, BOARD1_OFFSET_Y, previousPlayer1Board);
    drawBoard(player2, WINDOW_WIDTH - BOARD_OFFSET_X - BOARD_WIDTH, BOARD2_OFFSET_Y, previousPlayer2Board);

    drawTextInfo(player1, player2);

    drawNextBlock(player1, BOARD_OFFSET_X, BOARD1_OFFSET_Y + BOARD_HEIGHT + 20);
    drawNextBlock(player2, WINDOW_WIDTH - BOARD_OFFSET_X - BOARD_WIDTH, BOARD2_OFFSET_Y + BOARD_HEIGHT + 20);
}

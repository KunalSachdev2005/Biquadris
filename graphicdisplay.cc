#include "graphicdisplay.h"
#include <string>

GraphicDisplay::GraphicDisplay(Game* game) : game(game) {
    window = new XWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Initialize previous board states
    previousPlayer1Board.resize(18, std::vector<int>(11, EMPTY));
    previousPlayer2Board.resize(18, std::vector<int>(11, EMPTY));
}

GraphicDisplay::~GraphicDisplay() {
    delete window;
}

// Helper method for rendering
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
                if (block) {
                    currentColor = getColorForBlockType(block->getType());
                }
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


void GraphicDisplay::drawBoardWithGrid(Player* player, int offsetX, int offsetY, std::vector<std::vector<int>>& previousBoard) {
    // First, draw a black background for the entire board area
    window->fillRectangle(
        offsetX, 
        offsetY, 
        BOARD_WIDTH, 
        BOARD_HEIGHT, 
        XWindow::Color::Black
    );

    // Draw grid lines with White color for visibility
    for (int r = 0; r <= 18; ++r) {
        window->fillRectangle(
            offsetX, 
            offsetY + r * CELL_SIZE, 
            BOARD_WIDTH, 
            1, 
            XWindow::Color::White  // Grid line color
        );
    }
    for (int c = 0; c <= 11; ++c) {
        window->fillRectangle(
            offsetX + c * CELL_SIZE, 
            offsetY, 
            1, 
            BOARD_HEIGHT, 
            XWindow::Color::White  // Grid line color
        );
    }

    // Draw board cells
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

            // Always redraw to prevent disappearing blocks
            window->fillRectangle(
                offsetX + c * CELL_SIZE + 1, 
                offsetY + r * CELL_SIZE + 1, 
                CELL_SIZE - 2, 
                CELL_SIZE - 2, 
                currentColor
            );
            
            // Draw white border around each cell
    
            previousBoard[r][c] = currentColor;
        }
    }
}

void GraphicDisplay::drawNextBlock(Player* player, int offsetX, int offsetY) {
    // Clear the next block preview area first
    window->fillRectangle(
        offsetX, 
        offsetY, 
        11 * CELL_SIZE, 
        3 * CELL_SIZE, 
        XWindow::Color::White
    );

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

void GraphicDisplay::drawNextBlockSection(Player* player, int offsetX, int offsetY) {
    // Draw a white border for the next block section
    window->fillRectangle(
        offsetX, 
        offsetY, 
        BOARD_WIDTH, 
        3 * CELL_SIZE, 
        XWindow::Color::White
    );

    // Draw internal background
    window->fillRectangle(
        offsetX + 1, 
        offsetY + 1, 
        BOARD_WIDTH - 2, 
        3 * CELL_SIZE - 2, 
        XWindow::Color::Black
    );

    // Draw "Next:" text
    window->drawString(
        offsetX + TEXT_MARGIN,  
        offsetY + 20, 
        "Next:", 
        XWindow::Color::White
    );

    Block* nextBlock = player->getBoard()->getNextBlock();
    if (nextBlock) {
        int blockColor = getColorForBlockType(nextBlock->getType());
        
        // Draw next block preview (simplified representation)
        for (int r = 21; r < 24; ++r) {
            for (int c = 0; c < 11; ++c) {
                Cell* cell = player->getBoard()->at(r, c);
                
                if (cell->isOccupied()) {
                    window->fillRectangle(
                        offsetX + c * CELL_SIZE + 1, 
                        offsetY + (r - 21) * CELL_SIZE + 1, 
                        CELL_SIZE - 1, 
                        CELL_SIZE - 1, 
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

    // Set background to black
    window->fillRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, XWindow::Color::Black);

    // Draw board with grid for both players, regardless of turn
    drawBoardWithGrid(player1, BOARD_OFFSET_X, BOARD1_OFFSET_Y, previousPlayer1Board);
    drawBoardWithGrid(player2, WINDOW_WIDTH - BOARD_OFFSET_X - BOARD_WIDTH, BOARD2_OFFSET_Y, previousPlayer2Board);

    // Draw text information with White color for visibility
    window->drawString(TEXT_MARGIN, 30, "Level: " + std::to_string(player1->getLevel()->getLevel()), XWindow::Color::White);
    window->drawString(TEXT_MARGIN, 50, "Score: " + std::to_string(player1->getScore().getScore()), XWindow::Color::White);
    window->drawString(TEXT_MARGIN, 70, "High Score: " + std::to_string(player1->getScore().getHighScore()), XWindow::Color::White);

    window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 30, "Level: " + std::to_string(player2->getLevel()->getLevel()), XWindow::Color::White);
    window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 50, "Score: " + std::to_string(player2->getScore().getScore()), XWindow::Color::White);
    window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 70, "High Score: " + std::to_string(player2->getScore().getHighScore()), XWindow::Color::White);

    // Draw next block previews in a separate section
    drawNextBlockSection(player1, BOARD_OFFSET_X, BOARD1_OFFSET_Y + BOARD_HEIGHT + 20);
    drawNextBlockSection(player2, WINDOW_WIDTH - BOARD_OFFSET_X - BOARD_WIDTH, BOARD2_OFFSET_Y + BOARD_HEIGHT + 20);
}

void GraphicDisplay::drawTextInfo(Player* player1, Player* player2) {
    // Player 1 Info
    if (player1->getLevel()->getLevel() != previousPlayer1Level ||
        player1->getScore().getScore() != previousPlayer1Score ||
        player1->getScore().getHighScore() != previousPlayer1HighScore) {
        
        // Clear previous text area with black background
        window->fillRectangle(0, 0, WINDOW_WIDTH / 2, 100, XWindow::Color::Black);
        
        std::string levelStr = "Level: " + std::to_string(player1->getLevel()->getLevel());
        std::string scoreStr = "Score: " + std::to_string(player1->getScore().getScore());
        std::string highScoreStr = "High Score: " + std::to_string(player1->getScore().getHighScore());
        
        window->drawString(TEXT_MARGIN, 30, levelStr, XWindow::Color::White);
        window->drawString(TEXT_MARGIN, 50, scoreStr, XWindow::Color::White);
        window->drawString(TEXT_MARGIN, 70, highScoreStr, XWindow::Color::White);

        // Update previous values
        previousPlayer1Level = player1->getLevel()->getLevel();
        previousPlayer1Score = player1->getScore().getScore();
        previousPlayer1HighScore = player1->getScore().getHighScore();
    }

    // Player 2 Info (similar to Player 1)
    if (player2->getLevel()->getLevel() != previousPlayer2Level ||
        player2->getScore().getScore() != previousPlayer2Score ||
        player2->getScore().getHighScore() != previousPlayer2HighScore) {
        
        // Clear previous text area with black background
        window->fillRectangle(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, 100, XWindow::Color::Black);
        
        std::string levelStr = "Level: " + std::to_string(player2->getLevel()->getLevel());
        std::string scoreStr = "Score: " + std::to_string(player2->getScore().getScore());
        std::string highScoreStr = "High Score: " + std::to_string(player2->getScore().getHighScore());
        
        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 30, levelStr, XWindow::Color::White);
        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 50, scoreStr, XWindow::Color::White);
        window->drawString(WINDOW_WIDTH / 2 + TEXT_MARGIN, 70, highScoreStr, XWindow::Color::White);

        // Update previous values
        previousPlayer2Level = player2->getLevel()->getLevel();
        previousPlayer2Score = player2->getScore().getScore();
        previousPlayer2HighScore = player2->getScore().getHighScore();
    }
}

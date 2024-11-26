#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <vector>
#include <string>
#include "board.h"
#include "score.h"

class TextDisplay {
private:
    // Game boards and their display representation
    std::vector<std::vector<char>> board1Display;
    std::vector<std::vector<char>> board2Display;

    // Scores and levels
    int player1Level;
    int player2Level;
    Score player1Score;
    Score player2Score;

    // Next block preview
    std::string player1NextBlock;
    std::string player2NextBlock;

    // Render helper methods
    void renderBoard(const Board* board, std::vector<std::vector<char>>& boardDisplay);
    void renderNextBlock(Block* nextBlock, std::string& nextBlockDisplay);
    char getBlockChar(Type blockType);

public:
    // Constructor
    TextDisplay();

    // Main rendering methods
    void clear();
    void drawBoards(Board* player1Board, Board* player2Board);
    void drawScores(Score& player1Score, Score& player2Score);
    void render();

    // Special display methods
    void showFinalScores(Score& player1Score, Score& player2Score);
    void showInstructions();
};

#endif // TEXT_DISPLAY_H

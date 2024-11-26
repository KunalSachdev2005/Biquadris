#include "game.h"

// Constructor
Game::Game(const std::string& player1Name, const std::string& player2Name)
    : player1(player1Name), player2(player2Name), 
      currentPlayer(&player1), gameOver(false),
      commandInterpreter(), textDisplay() {
    initialize();
}

void Game::initialize() {
    // Set initial game state
    gameOver = false;
    
    // Reset players' states
    player1.resetTurn();
    player2.resetTurn();
    
    // Set first player's turn
    player1.setIsTurn(true);
    player2.setIsTurn(false);
    
    currentPlayer = &player1;
    
    // Initialize first blocks for both players
    player1.getBoard()->setNextBlock(player1.generateNextBlock());
    player2.getBoard()->setNextBlock(player2.generateNextBlock());
}

void Game::start() {
    // Game loop logic would be implemented here
    while (!gameOver) {
        updateDisplay();
        processCommand(commandInterpreter.getNextCommand());
        checkGameState();
    }
    
    handleGameOver();
}

void Game::switchTurns() {
    if (currentPlayer == &player1) {
        player1.setIsTurn(false);
        player2.setIsTurn(true);
        currentPlayer = &player2;
    } else {
        player1.setIsTurn(true);
        player2.setIsTurn(false);
        currentPlayer = &player1;
    }
}

void Game::processCommand(const std::string& command) {
    // Delegate command processing to command interpreter
    commandInterpreter.interpret(command, currentPlayer);
}

void Game::checkGameState() {
    // Check for game-ending conditions
    if (currentPlayer->getBoard()->isGameOver()) {
        gameOver = true;
    }
}

void Game::applySpecialAction() {
    // Implement special action logic when triggered
    // This would likely involve the current player choosing an action 
    // to apply to the opponent
}

void Game::handleGameOver() {
    // Determine winner, show final scores, etc.
    updateDisplay();
    showScores();
}

Player* Game::getCurrentPlayer() {
    return currentPlayer;
}

Player* Game::getOpponentPlayer() {
    return (currentPlayer == &player1) ? &player2 : &player1;
}

bool Game::isGameOver() const {
    return gameOver;
}

void Game::updateDisplay() {
    textDisplay.clear();
    textDisplay.drawBoards(player1.getBoard(), player2.getBoard());
    textDisplay.drawScores(player1.getScore(), player2.getScore());
    textDisplay.render();
}

void Game::showScores() {
    // Display final scores
    textDisplay.showFinalScores(player1.getScore(), player2.getScore());
}

void Game::printInstructions() {
    // Display game instructions
    textDisplay.showInstructions();
}

#include "game.h"
#include "level0.h"
#include "level1.h"  // Include appropriate level header
#include <iostream>
#include <stdexcept>

// Constructor
Game::Game(const std::string& player1Name, const std::string& player2Name)
    : player1(player1Name), player2(player2Name), 
      currentPlayer(&player1), gameOver(false),
      textDisplay(this) {
    initialize();
}

void Game::initialize() {

    player1.resetTurn();
    player2.resetTurn();
    // Set initial levels for players (example using Level0)
    player1.setLevel(new Level1(&player1));
    player2.setLevel(new Level1(&player2));

    // Set initial turn
    player1.setIsTurn(true);
    player2.setIsTurn(false);

    // Generate initial blocks for both players
    Block* block1 = player1.generateNextBlock();
    Block* block2 = player2.generateNextBlock();

    player1.getBoard()->setCurrentBlock(block1);
    player1.getBoard()->setNextBlock(player1.generateNextBlock());

    player2.getBoard()->setCurrentBlock(block2);
    player2.getBoard()->setNextBlock(player2.generateNextBlock());
}

void Game::start() {
    
    while (!gameOver) {
        updateDisplay();

        std::string command;
        std::cout << currentPlayer->getName() << "'s turn: ";
        std::getline(std::cin, command);

        try {
            processCommand(command);
            checkGameState();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    handleGameOver();
}

void Game::switchTurns() {
    currentPlayer->incrementTurns();

    if (currentPlayer->getTurns() > 5) {
        std::cout << currentPlayer->getName() << " has exceeded the turn limit. Game Over!\n";
        gameOver = true;
        return;  // Exit to prevent further turn switching
    }

    player1.setIsTurn(!player1.getIsTurn());
    player2.setIsTurn(!player2.getIsTurn());
    
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

void Game::processCommand(const std::string& command) {
    std::string interpretedCommand = commandInterpreter.interpretCommand(command);

    if (interpretedCommand == "Invalid command") {
        throw std::runtime_error("Invalid or ambiguous command");
    }

    Board* currentBoard = currentPlayer->getBoard();
    Block* currentBlock = currentBoard->getCurrentBlock();

    if (interpretedCommand == "left") {
        if (currentBoard->canMove(currentBlock, Direction::Left)) {
            currentBoard->moveBlock(currentBlock, Direction::Left);
        }
    }
    else if (interpretedCommand == "right") {
        if (currentBoard->canMove(currentBlock, Direction::Right)) {
            currentBoard->moveBlock(currentBlock, Direction::Right);
        }
    }
    else if (interpretedCommand == "down") {
        if (currentBoard->canMove(currentBlock, Direction::Down)) {
            currentBoard->moveBlock(currentBlock, Direction::Down);
        }
    }
    else if (interpretedCommand == "clockwise") {
        currentBoard->rotateBlock(currentBlock, Direction::Clockwise);
    }
    else if (interpretedCommand == "counterclockwise") {
        currentBoard->rotateBlock(currentBlock, Direction::CounterClockwise);
    }
    else if (interpretedCommand == "drop") {
        currentBoard->dropBlock(currentBlock);
        checkGameState();
        switchTurns();
    }
    // Add more command handlers as needed
}

void Game::checkGameState() {
    // Check for completed rows
    for (int row = 0; row < 21; ++row) {
        if (currentPlayer->getBoard()->isRowFull(row)) {
            currentPlayer->getBoard()->clearRow(row);
            currentPlayer->getScore().addScore(10);  // Adjust scoring as needed
        }
    }

    // Check if current player needs a new block
    if (!currentPlayer->getBoard()->getCurrentBlock()) {
        Block* newBlock = currentPlayer->generateNextBlock();
        currentPlayer->getBoard()->setCurrentBlock(currentPlayer->getBoard()->getNextBlock());
        currentPlayer->getBoard()->setNextBlock(newBlock);
    }
}

void Game::applySpecialAction() {
    // Implement special action logic between players
    // Could involve sending special blocks or modifying opponent's board
}

void Game::handleGameOver() {
    std::cout << "Game Over!" << std::endl;
    updateDisplay();
}

Player* Game::getCurrentPlayer() {
    return currentPlayer;
}

Player* Game::getOpponentPlayer() {
    return (currentPlayer == &player1) ? &player2 : &player1;
}

Player* Game::getPlayer1() {
    return &player1;
}

Player* Game::getPlayer2() {
    return &player2;
}

bool Game::isGameOver() const {
    return gameOver;
}

void Game::updateDisplay() {
    textDisplay.update();
}

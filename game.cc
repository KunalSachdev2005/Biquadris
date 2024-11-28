#include "game.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"  // Include appropriate level header
#include <iostream>
#include <stdexcept>

// Constructor
Game::Game(const std::string& player1Name, const std::string& player2Name, int player1Level, int player2Level)
    : player1(player1Name), player2(player2Name), 
      currentPlayer(&player1), gameOver(false),
      textDisplay(this) {
    initialize(player1Level, player2Level);
}

void Game::initialize(int player1Level, int player2Level) {
    // Reset player turns
    player1.resetTurn();
    player2.resetTurn();

    // Dynamically set levels for both players
    switch (player1Level) {
        //case 0: player1.setLevel(new Level0(&player1)); break;
        case 1: player1.setLevel(new Level1(&player1)); break;
        case 2: player1.setLevel(new Level2(&player1)); break;
        case 3: player1.setLevel(new Level3(&player1)); break;
        case 4: player1.setLevel(new Level4(&player1)); break;
        default:
            throw std::invalid_argument("Invalid level for player 1.");
    }

    switch (player2Level) {
        //case 0: player2.setLevel(new Level0(&player2)); break;
        case 1: player2.setLevel(new Level1(&player2)); break;
        case 2: player2.setLevel(new Level2(&player2)); break;
        case 3: player2.setLevel(new Level3(&player2)); break;
        case 4: player2.setLevel(new Level4(&player2)); break;
        default:
            throw std::invalid_argument("Invalid level for player 2.");
    }

    // Set initial turn
    player1.setIsTurn(true);  // Player 1 starts
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

int extractNumber(const std::string& command) {
    int num = 0;
    size_t i = 0;

    // Check for a number at the start of the command
    while (i < command.size() && std::isdigit(command[i])) {
        num = num * 10 + (command[i] - '0');
        i++;
    }

    return num;
}

void Game::switchTurns() {
    currentPlayer->incrementTurns();

    if (currentPlayer->getTurns() > 30) {
        std::cout << currentPlayer->getName() << " has exceeded the turn limit. Game Over!\n";
        gameOver = true;
        return;  // Exit to prevent further turn switching
    }

    player1.setIsTurn(!player1.getIsTurn());
    player2.setIsTurn(!player2.getIsTurn());
    
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

void Game::levelUp(Player* player) {
    int currentLevel = player->getLevel()->getLevel();

    if (currentLevel == 1) {
        player->setLevel(new Level2(player));  // If at Level1, upgrade to Level2
        std::cout << player->getName() << " leveled up to Level 2!" << std::endl;
    } 
    else if (currentLevel == 2) {
        player->setLevel(new Level3(player));  // If at Level2, upgrade to Level3
        std::cout << player->getName() << " leveled up to Level 3!" << std::endl;
    } 
    else if (currentLevel == 3) {
        player->setLevel(new Level4(player));  // If at Level3, upgrade to Level4
        std::cout << player->getName() << " leveled up to Level 4!" << std::endl;
    } 
    else {
        std::cout << player->getName() << " is already at the highest level!" << std::endl;
    }
}

// Level down player
void Game::levelDown(Player* player) {
    int currentLevel = player->getLevel()->getLevel();

    if (currentLevel == 4) {
        player->setLevel(new Level3(player));  // If at Level4, downgrade to Level3
        std::cout << player->getName() << " leveled down to Level 3!" << std::endl;
    } 
    else if (currentLevel == 3) {
        player->setLevel(new Level2(player));  // If at Level3, downgrade to Level2
        std::cout << player->getName() << " leveled down to Level 2!" << std::endl;
    } 
    else if (currentLevel == 2) {
        player->setLevel(new Level1(player));  // If at Level2, downgrade to Level1
        std::cout << player->getName() << " leveled down to Level 1!" << std::endl;
    } 
    else {
        std::cout << player->getName() << " is already at the lowest level!" << std::endl;
    }
}

void Game::processCommand(const std::string& command) {
    int repeatCount = extractNumber(command);
    std::string interpretedCommand = commandInterpreter.interpretCommand(command.substr(repeatCount > 0 ? std::to_string(repeatCount).length() : 0)); 

    if (interpretedCommand == "Invalid command") {
        throw std::runtime_error("Invalid or ambiguous command");
    }

    Board* currentBoard = currentPlayer->getBoard();
    Block* currentBlock = currentBoard->getCurrentBlock();
    bool isHeavy = currentBlock->isHeavy();
    int blockWeight = currentBlock->getWeight();

    if (repeatCount == 0) repeatCount = 1;

    if (interpretedCommand == "left" || interpretedCommand == "right") {
        Direction moveDir = (interpretedCommand == "left") ? Direction::Left : Direction::Right;

        for (int i = 0; i < repeatCount; ++i) {
            if (currentBoard->canMove(currentBlock, moveDir)) {
                currentBoard->moveBlock(currentBlock, moveDir);
            }
        }

        // Apply heavy effect if the block is heavy
        if (isHeavy) {
            for (int i = 0; i < blockWeight; ++i) {
                if (currentBoard->canMove(currentBlock, Direction::Down)) {
                    currentBoard->moveBlock(currentBlock, Direction::Down);
                } else {
                    checkGameState();
                    switchTurns();; // Stop if the block cannot move down further
                }
            }
        }
    } 
    else if (interpretedCommand == "clockwise" || interpretedCommand == "counterclockwise") {
        Direction rotateDir = (interpretedCommand == "clockwise") ? Direction::Clockwise : Direction::CounterClockwise;

        for (int i = 0; i < repeatCount; ++i) {
            currentBoard->rotateBlock(currentBlock, rotateDir);
        }

        // Apply heavy effect if the block is heavy and the level is 3 or 4
        if (isHeavy && (currentPlayer->getLevel()->getLevel() >= 3)) {
            for (int i = 0; i < blockWeight; ++i) {
                if (currentBoard->canMove(currentBlock, Direction::Down)) {
                    currentBoard->moveBlock(currentBlock, Direction::Down);
                } else {
                    checkGameState();
                    switchTurns(); // Stop if the block cannot move down further
                }
            }
        }
    }
    else if (interpretedCommand == "down") {
        for (int i = 0; i < repeatCount; ++i) {
            if (currentBoard->canMove(currentBlock, Direction::Down)) {
                currentBoard->moveBlock(currentBlock, Direction::Down);
            }
        }
    }
    else if (interpretedCommand == "drop") {
        currentBoard->dropBlock(currentBlock);
        checkGameState();
        switchTurns();
    }
    else if (interpretedCommand == "levelup") {
        for (int i = 0; i < repeatCount; ++i) {
            levelUp(currentPlayer);
        }
    }
    else if (interpretedCommand == "leveldown") {
        for (int i = 0; i < repeatCount; ++i) {
            levelDown(currentPlayer);
        }
    }
    // Add more command handlers as needed
}

void Game::checkGameState() {
    // Check for completed rows
    int rowsCleared = 0;
    int blockScore = 0;
    for (int row = 0; row < 21; ++row) {
        if (currentPlayer->getBoard()->isRowFull(row)) {
            ++rowsCleared;            
            blockScore += currentPlayer->getBoard()->clearRow(row);
        }
    }
    if (rowsCleared > 0) currentPlayer->getScore().addScore(blockScore + (rowsCleared + currentPlayer->getLevel()->getLevel())* (rowsCleared + currentPlayer->getLevel()->getLevel()));  // Adjust scoring as needed

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

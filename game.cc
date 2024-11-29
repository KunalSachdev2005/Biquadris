#include "game.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"  // Include appropriate level header
#include <iostream>
#include <stdexcept>
#include "blind.h"
#include "force.h"
#include "heavy.h"
#include "specialblock.h"

// Constructor
Game::Game(const std::string& player1Name, const std::string& player2Name, int startLevel, const std::string& scriptFile1,
            const std::string& scriptFile2, int randomSeed, int player1HighScore, int player2HighScore)
    : player1(player1Name), player2(player2Name),currentPlayer(&player1),textDisplay(this), scriptFile1(scriptFile1),
    scriptFile2(scriptFile2), randomSeed(randomSeed), startLevel(startLevel), graphicDisplay(new GraphicDisplay(this)) {
    player1.getScore().setHighScore(player1HighScore);
    player2.getScore().setHighScore(player2HighScore);
    initialize(startLevel, startLevel, player1HighScore, player2HighScore);
}

Game::~Game() {
    delete graphicDisplay;
}

void Game::initialize(int player1Level, int player2Level, int player1HighScore, int player2HighScore) {
    // Reset player turns
    player1.resetTurn();
    player2.resetTurn();

    // Set random seed (shared by all levels)
    if (randomSeed != 0) {
        std::srand(randomSeed);
    } else {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    // Dynamically set levels for both players
    switch (player1Level) {
        case 0: player1.setLevel(new Level0(scriptFile1, &player1)); break;
        case 1: player1.setLevel(new Level1(&player1)); break;
        case 2: player1.setLevel(new Level2(&player1)); break;
        case 3: player1.setLevel(new Level3(&player1)); break;
        case 4: player1.setLevel(new Level4(&player1)); break;
        default:
            throw std::invalid_argument("Invalid level for player 1.");
    }

    switch (player2Level) {
        case 0: player2.setLevel(new Level0(scriptFile2, &player2)); break;
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

int Game::getStartLevel() const{ return startLevel; }

int Game::getSeed() const { return randomSeed;}

void Game::start() {
    bool gameActive = true;
    
    while (gameActive) {
        // Check if the game is ongoing or just ended
        if (!player1.isGameOver() && !player2.isGameOver()) {
            updateDisplay();
            std::cout << currentPlayer->getName() << "'s turn: ";
        } else {
            handleGameOver();
            std::cout << "Game ended. Enter 'restart' or 'quit' to continue: ";
        }

        std::string command;
        std::getline(std::cin, command);

        try {
            if (command == "quit") {
                gameActive = false;
            } else if (command == "restart") {
                int player1score = std::max(player1.getScore().getHighScore(), player1.getScore().getScore());
                int player2score = std::max(player2.getScore().getHighScore(), player2.getScore().getScore());

                Game game(player1.getName(), player2.getName(), startLevel, scriptFile1, scriptFile2, randomSeed, player1score, player2score);
                game.start();
                
                // Exit the current game loop after restarting
                gameActive = false;
            } else if (!player1.isGameOver() && !player2.isGameOver()) {
                processCommand(command);
                checkGameState();
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
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
    player1.setIsTurn(!player1.getIsTurn());
    player2.setIsTurn(!player2.getIsTurn());
    
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

void Game::levelUp(Player* player) {
    int currentLevel = player->getLevel()->getLevel();
    if (currentLevel == 0) {
        player->setLevel(new Level1(player));
        std::cout << player->getName() << " leveled up to Level 1!" << std::endl;
    }
    else if (currentLevel == 1) {
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
    else if (currentLevel == 1) {
        std::string file = player == &player1? scriptFile1 : scriptFile2;
        player->setLevel(new Level0(file, player));  
        std::cout << player->getName() << " leveled down to Level 0!" << std::endl;
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

    if (interpretedCommand == "norandom") {
        if (currentPlayer->getLevel()->getLevel() >= 3) {
            std::string filePath = command.substr(command.find(' ') + 1);
            currentPlayer->getLevel()->setSequenceMode(filePath);
        } else {
            throw std::runtime_error("norandom command is only valid for levels 3 and 4.");
        }
    }
    else if (interpretedCommand == "random") {
        if (currentPlayer->getLevel()->getLevel() >= 3) {
            currentPlayer->getLevel()->setRandomMode();
        } else {
            throw std::runtime_error("random command is only valid for levels 3 and 4.");
        }
    }
    else if (interpretedCommand == "sequence") {
        std::string filePath = command.substr(command.find(' ') + 1);
        std::ifstream sequenceFile(filePath);
        if (!sequenceFile) {
            throw std::runtime_error("Unable to open sequence file: " + filePath);
        }

        std::string line;
        while (std::getline(sequenceFile, line)) {
            processCommand(line);
        }
    }
    else if (interpretedCommand == "I" || interpretedCommand == "J" || interpretedCommand == "L" || interpretedCommand == "O" || 
             interpretedCommand == "S" || interpretedCommand == "Z" || interpretedCommand == "T") {
                currentBoard->getCurrentBlock()->clearOldCells();
                Cell* baseCell = currentBoard->at(3, 0);
                Block* newBlock = nullptr;
                int level = currentPlayer->getLevel()->getLevel();

                if (interpretedCommand == "I") currentBoard->setCurrentBlock( newBlock = new IBlock(level, baseCell) );
                else if (interpretedCommand == "J") currentBoard->setCurrentBlock( newBlock = new JBlock(level, baseCell) );
                else if (interpretedCommand == "L") currentBoard->setCurrentBlock( newBlock = new LBlock(level, baseCell) );
                else if (interpretedCommand == "O") currentBoard->setCurrentBlock( newBlock = new OBlock(level, baseCell) );
                else if (interpretedCommand == "S") currentBoard->setCurrentBlock( newBlock = new SBlock(level, baseCell) );
                else if (interpretedCommand == "Z") currentBoard->setCurrentBlock( newBlock = new ZBlock(level, baseCell) );
                else if (interpretedCommand == "T") currentBoard->setCurrentBlock( newBlock = new TBlock(level, baseCell) );

                if (level >= 3) {
                    newBlock->setHeavy(true);
                    newBlock->setWeight(1);
                }
             }
    else if (interpretedCommand == "left" || interpretedCommand == "right") {
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
        currentPlayer->incrementTurn();
        currentBoard->setBlinded(false);
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
    else if (interpretedCommand == "restart") {
            int player1score = std::max(player1.getScore().getHighScore(), player1.getScore().getScore());
            int player2score = std::max(player2.getScore().getHighScore(), player2.getScore().getScore());

            Game game(player1.getName(), player2.getName(), startLevel, scriptFile1, scriptFile2, randomSeed, player1score, player2score);

            game.start();

        }
    }
    // Add more command handlers as needed


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
    if (rowsCleared > 0) {
        currentPlayer->getScore().addScore(blockScore + (rowsCleared + currentPlayer->getLevel()->getLevel())* (rowsCleared + currentPlayer->getLevel()->getLevel()));  // Adjust scoring as needed
    }
    else if (currentPlayer->getLevel()->getLevel() >= 4) {
        // Check if the drop counter triggers a special block
        int blocksDropped = currentPlayer->getBlocksSinceClear();
        if (blocksDropped == 5) {
            dropSpecialBlock(currentPlayer);
            currentPlayer->setBlocksSinceClear(0);
        }
    }

    if(rowsCleared > 0) {
        std::cout << "Special action triggered! Choose your action (blind, heavy, force): ";
            std::string actionChoice;
            std::cin >> actionChoice;

            SpecialAction* action = nullptr;
            if (actionChoice == "blind") {
                action = new Blind(currentPlayer, getOpponentPlayer());
            } else if (actionChoice == "heavy") {
                action = new Heavy(currentPlayer, getOpponentPlayer());
            } else if (actionChoice == "force") {
                std::cout << "Choose block type for force action (I, J, L, O, S, T, Z): ";
                char blockTypeChar;
                std::cin >> blockTypeChar;
                Type blockType = charToType(blockTypeChar); // Implement charToType to convert char to Type enum
                action = new Force(currentPlayer, getOpponentPlayer(), blockType);
            } 

            if (action) {
                applySpecialAction(action);
                delete action;
            }
    }

    // Check if current player needs a new block
    if (!currentPlayer->getBoard()->getCurrentBlock()) {
        Block* newBlock = currentPlayer->generateNextBlock();
        if(!currentPlayer->getBoard()->setCurrentBlock(currentPlayer->getBoard()->getNextBlock())) currentPlayer->setGameOver();
        currentPlayer->getBoard()->setNextBlock(newBlock);
    }
}

void Game::dropSpecialBlock(Player* p) {
    Board* b = p->getBoard();
    Block* newBlock = b->at(0,5)->isOccupied()? nullptr : new SPBlock(b->at(0,5));
    b->dropBlock(newBlock);
}

void Game::applySpecialAction(SpecialAction* action) {
    action->execute();
}

Type Game::charToType(char ch) {
    switch(ch) {
        case 'I': return Type::I; 
        case 'J': return Type::J; 
        case 'T': return Type::T; 
        case 'S': return Type::S; 
        case 'Z': return Type::Z; 
        case 'O': return Type::O; 
        case 'L': return Type::L;
        default: return Type::I;
    }
}

void Game::handleGameOver() {
    std::cout << "Game Over!" << std::endl;

    // Determine the winner
    int player1Score = player1.getScore().getScore();
    int player2Score = player2.getScore().getScore();

    if (player1.isGameOver() && player2.isGameOver()) {
        std::cout << "It's a tie!" << std::endl;
    } else if (player1.isGameOver()) {
        std::cout << player2.getName() << " wins with a score of " << player2Score << "!" << std::endl;
    } else if (player2.isGameOver()) {
        std::cout << player1.getName() << " wins with a score of " << player1Score << "!" << std::endl;
    }

    // Print final scores and high scores
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

void Game::updateDisplay() {
    textDisplay.update();
    graphicDisplay->update();
}

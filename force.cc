#include <iostream>
#include "force.h"

void Force::execute() {
    // Change the opponent's current block to the forced block type
    opponent->getBoard()->getCurrentBlock()->clearOldCells();
    Block* forcedBlock;
    
    // Determine which block type to force
    switch (type) 
    {
        case Type::I: forcedBlock = new IBlock(opponent->getLevel()->getLevel(), opponent->getBoard()->at(3,0)); break;
        case Type::J: forcedBlock = new JBlock(opponent->getLevel()->getLevel(), opponent->getBoard()->at(3,0)); break;
        case Type::T: forcedBlock = new TBlock(opponent->getLevel()->getLevel(), opponent->getBoard()->at(3,0)); break;
        case Type::Z: forcedBlock = new ZBlock(opponent->getLevel()->getLevel(), opponent->getBoard()->at(3,0)); break;
        case Type::S: forcedBlock = new SBlock(opponent->getLevel()->getLevel(), opponent->getBoard()->at(3,0)); break;
        case Type::L: forcedBlock = new LBlock(opponent->getLevel()->getLevel(), opponent->getBoard()->at(3,0)); break;
        case Type::O: forcedBlock = new OBlock(opponent->getLevel()->getLevel(), opponent->getBoard()->at(3,0)); break;
        default: forcedBlock = new IBlock(opponent->getLevel()->getLevel(), opponent->getBoard()->at(3,0));
    }
   
    if (!opponent->getBoard()->setCurrentBlock(forcedBlock)) {
        opponent->setGameOver();
    }
}

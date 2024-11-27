#include <iostream>
#include "CommandInterpreter.h"
#include "board.h"
#include "block.h"
#include "cell.h"
#include "iblock.h"
#include "jblock.h"
#include "sblock.h"
#include "tblock.h"
#include "oblock.h"
#include "lblock.h"
#include "zblock.h"
#include "player.h"
#include "level.h"
#include "level2.h"

int main() {
    Player* p = new Player();
    Board* b = p->getBoard();
    Level* l = new Level2(p);
    p->setLevel(l);
    Block* block = p->generateNextBlock();
    b->setNextBlock(block);
    b->printTextDisplay();
    b->setCurrentBlock(b->getNextBlock());
    b->setNextBlock(p->generateNextBlock());
    b->printTextDisplay();
    b->moveBlock(b->getCurrentBlock(), Direction::Right);
    b->moveBlock(b->getCurrentBlock(), Direction::Right);
    b->moveBlock(b->getCurrentBlock(), Direction::Right);
    b->moveBlock(b->getCurrentBlock(), Direction::Down);
    b->printTextDisplay();
    b->setCurrentBlock(b->getNextBlock());
    b->setNextBlock(p->generateNextBlock());
    b->printTextDisplay();
    return 0;
}

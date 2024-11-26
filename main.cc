#include <iostream>
#include "CommandInterpreter.h"
#include "board.h"
#include "block.h"
#include "cell.h"
#include "iblock.h"

int main() {
    Board b;
    Direction d = Direction::Right;
    Block* block = new IBlock(0, b.at(0,3));
    std::cout << block->getBaseCell()->getCol() << block->getBaseCell()->getRow() << std::endl;
    b.setCurrentBlock(block);
    b.moveBlock(d);
    std::cout << block->getBaseCell()->getCol() << block->getBaseCell()->getRow() << std::endl;
    b.dropBlock(block);
    std::cout << block->getBaseCell()->getCol() << block->getBaseCell()->getRow() << std::endl;
    return 0;
}

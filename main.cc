#include <iostream>
#include "CommandInterpreter.h"
#include "board.h"
#include "block.h"
#include "cell.h"
#include "iblock.h"
#include "jblock.h"
#include "oblock.h"

int main() {
    Board b;
    Direction d = Direction::Right;
    Block* block = new OBlock(0, b.at(0,3));
    b.printTextDisplay();
    b.moveBlock(block, Direction::Down);
    b.moveBlock(block, Direction::Down);
    b.moveBlock(block, Direction::Down);
    b.moveBlock(block, Direction::Down);
    b.printTextDisplay();
    b.setCurrentBlock(block);
    b.rotateBlock(Direction::Clockwise);
    b.printTextDisplay();
    return 0;
}

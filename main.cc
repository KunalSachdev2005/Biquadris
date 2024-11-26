#include <iostream>
#include "CommandInterpreter.h"
#include "board.h"
#include "block.h"
#include "cell.h"
#include "iblock.h"
#include "jblock.h"
#include "sblock.h"

int main() {
    Board b;
    Direction d = Direction::Right;
    Block* block = new JBlock(0, b.at(4,8));
    Block* block2 = new SBlock(0, b.at(8,6));
    b.printTextDisplay();
    b.dropBlock(block);
    b.printTextDisplay();
    b.setCurrentBlock(block);
    b.rotateBlock(block, Direction::Clockwise);
    b.moveBlock(block, Direction::Left);
    b.moveBlock(block, Direction::Left);
    b.moveBlock(block, Direction::Left);
    b.printTextDisplay();
    b.dropBlock(block);
    b.printTextDisplay();
    b.rotateBlock(block, Direction::CounterClockwise);
    b.printTextDisplay();
    b.dropBlock(block);
    b.printTextDisplay();
    b.dropBlock(block2);
    b.printTextDisplay();
    return 0;
}

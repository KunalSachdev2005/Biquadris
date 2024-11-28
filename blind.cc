#include "blind.h"

void Blind::execute() {
    // Cover columns 3-9, rows 3-12 with '?'
    Board* opponentBoard = opponent->getBoard();
    std::cout << "Blinding " << opponent->getName();
    opponentBoard->setBlinded(true);
}
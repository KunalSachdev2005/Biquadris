#include "blind.h"

void Blind::execute() {
    // Cover columns 3-9, rows 3-12 with '?'
    
    // Fetch opponent's board
    Board* opponentBoard = opponent->getBoard();
    
    // Notify that the opponent is being blinded
    std::cout << "Blinding " << opponent->getName() << std::endl;
    
    // Apply blindness effect
    opponentBoard->setBlinded(true);
}

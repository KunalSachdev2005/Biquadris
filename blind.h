#ifndef BLIND_H
#define BLIND_H

#include <iostream>

#include "board.h"
#include "specialaction.h"

// Class declaration
class Blind : public SpecialAction {
public:
    // Constructor
    Blind(Player* player, Player* opponent) : SpecialAction(player, opponent) {}

    // Override execute function
    void execute() override;
};

#endif // BLIND_H

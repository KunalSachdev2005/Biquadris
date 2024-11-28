// blind.h
#ifndef BLIND_H
#define BLIND_H

#include "specialaction.h"
#include "board.h"
#include <iostream>

class Blind : public SpecialAction {
public:
    Blind(Player* player, Player* opponent) : SpecialAction(player, opponent) {}

    void execute() override;
};

#endif // BLIND_H

// specialaction.h
#ifndef SPECIALACTION_H
#define SPECIALACTION_H

#include "player.h"

class SpecialAction {
protected:
    Player* player;   // Player who triggered the special action
    Player* opponent; // Opponent affected by the special action

public:
    SpecialAction(Player* player, Player* opponent) : player(player), opponent(opponent) {}
    virtual ~SpecialAction() = default;

    // Abstract method to execute the action
    virtual void execute() = 0;
};

#endif // SPECIALACTION_H

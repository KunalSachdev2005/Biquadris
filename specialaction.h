#ifndef SPECIALACTION_H
#define SPECIALACTION_H

#include "player.h"  // Include the player class dependency

// Abstract base class
class SpecialAction {
protected:
    Player* player;   // Player who triggered the special action
    Player* opponent; // Opponent affected by the special action

public:
    // Constructor
    SpecialAction(Player* player, Player* opponent);

    // Virtual destructor (in case derived classes need one)
    virtual ~SpecialAction() = default;

    // Abstract method that must be implemented by derived classes to execute the action
    virtual void execute() = 0;
};

#endif // SPECIALACTION_H

#ifndef FORCE_H
#define FORCE_H

#include "block.h"
#include "specialaction.h"

class Force : public SpecialAction {
private:
    Type type;  // Block type that the player wants to force on the opponent

public:
    Force(Player* player, Player* opponent, Type type) : SpecialAction(player, opponent), type(type) {}
    
    void execute() override;
};

#endif // FORCE_H

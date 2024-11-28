// heavy.h
#ifndef HEAVY_H
#define HEAVY_H

#include "specialaction.h"

class Heavy : public SpecialAction {
public:
    Heavy(Player* player, Player* opponent) : SpecialAction(player, opponent) {}

    void execute() override;
};

#endif // HEAVY_H

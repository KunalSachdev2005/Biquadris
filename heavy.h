#ifndef HEAVY_H
#define HEAVY_H

#include "specialaction.h"

class Heavy : public SpecialAction {
public:
    // Constructor
    Heavy(Player* player, Player* opponent);

    // Override execute function
    void execute() override;
};

#endif // HEAVY_H

#include "heavy.h"

const int SPECIAL_HEAVY_WEIGHT = 2;

// Constructor
Heavy::Heavy(Player* player, Player* opponent) : SpecialAction(player, opponent) {}

void Heavy::execute() {
    // Update the current block with the new weight and heavy status
    opponent->getBoard()->getCurrentBlock()->setWeight(SPECIAL_HEAVY_WEIGHT);
    opponent->getBoard()->getCurrentBlock()->setHeavy(true);
}

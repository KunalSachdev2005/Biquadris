#include "heavy.h"

void Heavy::execute()  {
    opponent->getBoard()->getCurrentBlock()->setWeight(2);
    opponent->getBoard()->getCurrentBlock()->setHeavy(true);
}
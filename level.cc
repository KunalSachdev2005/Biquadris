#include "level.h"

Level::Level(int levelNumber, Player* player) : level(levelNumber), player(player) {}

Level::~Level() {}

int Level::getLevel() { return level;}

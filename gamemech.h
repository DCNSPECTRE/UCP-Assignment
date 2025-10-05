#ifndef GAMEMECHANICS_H
#define GAMEMECHANICS_H

#include "escape.h"

void handleInput(char input, gameState* game);
void triggerTrap(gameState* game);
void spreadWater(gameState* game);
Player findPlayer(const gameMapInfo* mapInfo);

#endif
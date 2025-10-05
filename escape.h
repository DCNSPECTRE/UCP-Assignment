#ifndef ESCAPE_H
#define ESCAPE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileimport.h"
#include "color.h"
#include "terminal.h"

typedef struct Player{
    int row;
    int col;
}Player;

typedef struct gameState{
    int trapTrigger;
    int flooded;
    int goalReached;
    Player player;
    gameMapInfo* mapInfo;
    char** displayMap;
    int gameRunning;
}gameState;

void printDisplayMap(char** map, const gameMapInfo* mapInfo);
Player findPlayer(const gameMapInfo* mapInfo);
void handleInput(char input, gameState* game);
void triggerTrap(gameState* game);
void spreadWater(gameState* game);
gameState* undoMoveDo(undoNode** head);
void undoMoveStore(undoNode** head, gameState* game);

typedef struct undoNode{
    void* data;
    struct undoNode* next;
}undoNode;

#endif
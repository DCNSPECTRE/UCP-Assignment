#ifndef ESCAPE_H
#define ESCAPE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileimport.h"
#include "color.h"
#include "terminal.h"
#include "linkedlist.h"

/* This is the struct for the player position */
typedef struct {
    int row;
    int col;
}Player;

/* This is the struct that stores the game state info such as the game map and the info, the game states for the traps, flooding, goals, game running etc.*/
typedef struct{
    int trapTrigger;
    int flooded;
    int goalReached;
    Player player;
    gameMapInfo* mapInfo;
    char** displayMap;
    int gameRunning;
}gameState;

/* all of the function prototypes*/
void printDisplayMap(char** map, const gameMapInfo* mapInfo);
Player findPlayer(const gameMapInfo* mapInfo);
void handleInput(char input, gameState* game, linkedListNode** undoStack);
void triggerTrap(gameState* game);
void spreadWater(gameState* game);
void freeGameState(void* data);
char ** copyDisplayMap(char** src, int rows, int cols);

#endif
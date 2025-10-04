#ifndef ESCAPE_H
#define ESCAPE_H

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "fileimport.h"
#include "color.h"
#include "terminal.h"

typedef struct {
    int row;
    int col;
}Player;

typedef struct{
    int trapTrigger;
    int flooded;
    int goalReached;
    Player player;
    gameMapInfo* mapInfo;
    char** displayMap;
    int gameRunning;
}gameState;


#endif
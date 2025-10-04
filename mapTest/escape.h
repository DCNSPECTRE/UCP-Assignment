#ifndef ESCAPE_H
#define ESCAPE_H

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "fileimport.h"

typedef struct {
    int row;
    int col;
}Player;

typedef struct{
    int trapTrigger;
    Player player;
    gameMapInfo* mapInfo;
    char** displayMap;
}gameState;


#endif
#ifndef FILEIMPORT_H
#define FILEIMPORT_H

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "color.h"

typedef struct gameMapInfo{
    int rows;
    int cols;
    int ** mapMatrix;
}gameMapInfo;

gameMapInfo* importMap(const char * mapPath);
char** createGameMap(const gameMapInfo * mapData);
void freeMapData(gameMapInfo* mapData);
void freeDisplayMap(char** displayMap, gameMapInfo* mapData);

#endif
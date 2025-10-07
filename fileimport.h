#ifndef FILEIMPORT_H
#define FILEIMPORT_H

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "color.h"

/* Struct that holds the map info such as the no of rows, cols and the double pointer to an int which is the mapMatrix (the array of numbers)*/
typedef struct gameMapInfo{
    int rows;
    int cols;
    int ** mapMatrix;
}gameMapInfo;

/* Function prototypes */
gameMapInfo* importMap(const char * mapPath);
char** createGameMap(const gameMapInfo * mapData);
void freeMapData(gameMapInfo* mapData);
void freeDisplayMap(char** displayMap, gameMapInfo* mapData);

#endif
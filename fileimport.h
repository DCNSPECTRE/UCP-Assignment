#ifndef FILEIMPORT_H
#define FILEIMPORT_H

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "color.h"

typedef struct{
    int rows;
    int cols;
    int ** mapMatrix;
}gameMapInfo;

gameMapInfo * importMap(const char * mapPath);
void freeMapData(gameMapInfo* mapData);
void freeDisplayMap(char** displayMap, const gameMapInfo* mapData);

#endif
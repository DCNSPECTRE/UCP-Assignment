#include "fileimport.h"

gameMapInfo* importMap(const char * mapPath){
    FILE * mapPtr = fopen(mapPath, "r");
    if(mapPath == NULL){
        printf("Enter map path, or check directory\n");
        return NULL;
    }

    gameMapInfo * gameMap = malloc(sizeof(gameMapInfo));
    if(gameMap = NULL){
        fclose(mapPtr);
        return NULL;
    }

    fscanf(mapPtr, "%d %d", &gameMap->rows, &gameMap->cols);

    gameMap->mapMatrix = malloc(gameMap->rows * sizeof(int*));

    int i, j;

    for(i = 0; i < gameMap->rows; i++){
        gameMap->mapMatrix[i] = malloc(gameMap->cols * sizeof(int));
    }

    for(i = 0; i < gameMap->rows; i++){
        for(j = 0; j < gameMap->cols; j++){
            fscanf(mapPtr, "%d", &gameMap->mapMatrix[i][j]);
        }
    }

    fclose(mapPtr);

    return gameMap;
}


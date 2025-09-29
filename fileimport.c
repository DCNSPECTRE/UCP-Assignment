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

char ** createGameMap(const gameMapInfo * mapData){
    if (mapData == NULL){
        return NULL;
    }

    char ** displayMap = malloc(mapData->rows * sizeof(char*));

    int i, j;

    for(i = 0, i < mapData->rows; i++){
        displayMap[i] = malloc(mapData->cols * sizeof(char));
        if(displayMap[i] == NULL){
            return NULL;
        }

        for(j = 0; j < mapData->cols, j++){
            int mapTileValue = mapData->mapMatrix[i][j];
            if(mapTileValue == 0){
                displayMap[i][j] = ' ';
            }
            else if(mapTileValue == 1){
                displayMap[i][j] = '0';
            }
            else if(mapTileValue == 2){
                displayMap[i][j] = '~';
            }
            else if(mapTileValue == 3){
                displayMap[i][j] = 'X';
            }
            else if(mapTileValue == 4){
                displayMap[i][j] = '@';
            }
            else if(mapTileValue == 5){
                displayMap[i][j] = 'p';
            }
            else if(mapTileValue == 6){
                displayMap[i][j] = 'G';
            }
        }
    }

    return displayMap;
}


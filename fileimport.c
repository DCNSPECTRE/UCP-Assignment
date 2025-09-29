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
                displayMap[i][j] = 'O';
            }
            else if(mapTileValue == 2){
                setForeground("white")
                setBackground("blue")
                displayMap[i][j] = '~';
                setForeground("reset")
                setBackground("reset")             
            }
            else if(mapTileValue == 3){
                displayMap[i][j] = 'X';
            }
            else if(mapTileValue == 4){
                setForeground("white")
                setBackground("red")
                displayMap[i][j] = '@';
                setForeground("reset")
                setBackground("reset")
            }
            else if(mapTileValue == 5){
                displayMap[i][j] = 'P';
            }
            else if(mapTileValue == 6){
                setForeground("black")
                setBackground("green")
                displayMap[i][j] = 'G';
                setForeground("reset")
                setBackground("reset")
            }
        }
    }

    return displayMap;
}

/*NOTE TO SELF: ALWAYS DO THIS LAST OR I CANT FREE THE DISPLAY MAP*/
/*NOTE TO SELF: ALWAYS DO THIS LAST OR I CANT FREE THE DISPLAY MAP*/
/*NOTE TO SELF: ALWAYS DO THIS LAST OR I CANT FREE THE DISPLAY MAP*/
void freeMapData(gameMapInfo* mapData){
    if(mapData == NULL){
        return NULL;
    }

    int i;

    for(i = 0; i < mapData->rows, i++){
        free(mapData->mapMatrix[i]);
    }

    free(mapData->mapMatrix);
    free(mapData);

}

void freeDisplayMap(char** displayMap, gameMapInfo* mapData){
    if(displayMap == NULL){
        return NULL;
    }

    int i;

    for(i = 0; i < mapData->rows; i++){
        free(displayMap[i]);
    }

    free(displayMap);
}
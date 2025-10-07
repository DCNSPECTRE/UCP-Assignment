#include "fileimport.h"

/* Imports the map from a given path and returns a pointer to a gameMapInfo struct containing the map data.*/
gameMapInfo* importMap(const char * mapPath){
    int i, j;
    gameMapInfo * gameMap = NULL;
    FILE * mapPtr; 
    
    /* If the map path provided is invalid then it throws this error.*/
    if(mapPath == NULL){
        printf("Enter map path, or check directory\n");
        return NULL;
    }
    
    /* the pointer to the file mapPtr is opened in read mode from the path */
    mapPtr = fopen(mapPath, "r");
    
    /* If the file pointer is NULL then it throws this error.*/
    if(mapPtr == NULL){
        printf("Error opening the map!\n");
        return NULL;
    }
    /* Allocating memory for the gameMapInfo struct */
    gameMap = malloc(sizeof(gameMapInfo));

    /* If the memory allocation fails then it throws this error.*/
    if(gameMap == NULL){
        fclose(mapPtr);
        return NULL;
    }
    
    /* The first two integers in the map file are read and stored as the number of rows and columns in the mapMatrix */
    fscanf(mapPtr, "%d %d", &gameMap->rows, &gameMap->cols);

    /* Allocating the first dimension of the mapMatrix which is in the gameMap (gameMapInfo) struct*/
    gameMap->mapMatrix = malloc(gameMap->rows * sizeof(int*));

    /* the for loops allocate memory for each column in the 2D array and read the map data from the file into the mapMatrix */
    for(i = 0; i < gameMap->rows; i++){
        gameMap->mapMatrix[i] = malloc(gameMap->cols * sizeof(int));
    }

    /* now we allocate each int that is read from the maps ith row and jth column into this array*/
    for(i = 0; i < gameMap->rows; i++){
        for(j = 0; j < gameMap->cols; j++){
            fscanf(mapPtr, "%d", &gameMap->mapMatrix[i][j]);
        }
    }
    /*once we have read throug the file, we close the file and return the game map*/
    fclose(mapPtr);    
    return gameMap;
}
/* Creates a display map (2D char array) from the gameMapInfo struct by mapping integer values to the respective characters.*/
/* the function takes in a pointer to the gameMapInfo struct that is constant and returns a double pointer to char (2D char array) which is the actual map*/
char ** createGameMap(const gameMapInfo * mapData){
    int i, j;
    char ** displayMap = NULL;
    
    /* If the mapData pointer is NULL then it returns NULL */
    if (mapData == NULL){
        return NULL;
    }

    /* Allocating memory for the first dimension of the 2D char array (rows) */
    displayMap = malloc(mapData->rows * sizeof(char*));

    /* If the memory allocation fails then it returns NULL */
    for(i = 0; i < mapData->rows; i++){
        displayMap[i] = malloc(mapData->cols * sizeof(char));
        if(displayMap[i] == NULL){
            return NULL;
        }

        /* Mapping the integer values from the mapMatrix to their respective characters in the displayMap */
        for(j = 0; j < mapData->cols; j++){
            int mapTileValue = mapData->mapMatrix[i][j];
            if(mapTileValue == 0){
                displayMap[i][j] = ' ';
            }
            else if(mapTileValue == 1){
                displayMap[i][j] = 'O';
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
                displayMap[i][j] = 'P';
            }
            else if(mapTileValue == 6){
                displayMap[i][j] = 'G';
            }
        }
    }
    /* Return the created display map */
    return displayMap;
}

/*NOTE TO SELF: ALWAYS DO THIS LAST OR I CANT FREE THE DISPLAY MAP*/
/*NOTE TO SELF: ALWAYS DO THIS LAST OR I CANT FREE THE DISPLAY MAP*/
/*NOTE TO SELF: ALWAYS DO THIS LAST OR I CANT FREE THE DISPLAY MAP*/
/* This function takes hte pointer to the gameMapInfo struct that is constant nd frees the malloced map matrix and the map data itself*/
void freeMapData(gameMapInfo* mapData){
    int i;
    if(mapData == NULL){
        return;
    }

    for(i = 0; i < mapData->rows; i++){
        free(mapData->mapMatrix[i]);
    }

    free(mapData->mapMatrix);
    free(mapData);

}

/* This function frees the malloced display map (2D char array)*/
void freeDisplayMap(char** displayMap, gameMapInfo* mapData){
    int i;
    if(displayMap == NULL){
        return;
    }

    for(i = 0; i < mapData->rows; i++){
        free(displayMap[i]);
    }

    free(displayMap);
}
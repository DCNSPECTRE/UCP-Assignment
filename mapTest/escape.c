#include <stdio.h>
#include <stdlib.h>
#include "escape.h"
#include "fileimport.h"
#include "color.h"

void printDisplayMap(char** map, const gameMapInfo* mapInfo);
Player findPlayer(const gameMapInfo* mapInfo);
void handleInput(char input, gameState* game);
void triggerTrap(gameState* game);
void spreadWater(gameState* game);


int main(int argc, char *argv[])
{
    gameMapInfo* mapInfo = NULL;
    char** displayMap = NULL;

    if (argc != 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    printf("Attempting to import map from '%s'...\n", argv[1]);

    mapInfo = importMap(argv[1]);

    if (mapInfo == NULL)
    {
        printf("Failed to import map data. Exiting.\n");
        return 1;
    }

    printf("Map imported successfully! Dimensions: %d rows, %d cols\n\n", mapInfo->rows, mapInfo->cols);

    displayMap = createGameMap(mapInfo);

    if (displayMap == NULL)
    {
        printf("Failed to create the display map. Exiting.\n");
        freeMapData(mapInfo);
        return 1;
    }


    printDisplayMap(displayMap, mapInfo);

    printf("Cleaning up memory...\n");
    freeDisplayMap(displayMap, mapInfo);
    freeMapData(mapInfo);
    printf("Memory freed. Test complete.\n");

    return 0;
}

void printDisplayMap(char** map, const gameMapInfo* mapInfo)
{
    int i, j;

    for (j = 0; j < mapInfo->cols + 2; j++)
    {
        printf("*");
    }
    printf("\n");

    for (i = 0; i < mapInfo->rows; i++)
    {
        printf("*");
        for (j = 0; j < mapInfo->cols; j++)
        {
            char currentTile = map[i][j];
            if (currentTile == '~')
            {
                setBackground("blue");
                printf("%c", currentTile);
                setBackground("reset");
            }
            else if (currentTile == '@')
            {
                setBackground("red");
                printf("%c", currentTile);
                setBackground("reset");
            }
            else if (currentTile == 'G')
            {
                setBackground("green");
                printf("%c", currentTile);
                setBackground("reset");
            }
            else
            {
                printf("%c", currentTile);
            }
        }
        printf("*\n");
    }

    for (j = 0; j < mapInfo->cols + 2; j++)
    {
        printf("*");
    }
    printf("\n");
}

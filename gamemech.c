#include "gamemech.h"

void handleInput(char input, gameState* game, undoNode** undoHead){
    int nextRow = game->player.row;
    int nextCol = game->player.col;

    if(input == 'w'){
        nextRow --;
    }
    else if(input == 's'){
        nextRow ++;
    }
    else if(input == 'a'){
        nextCol --;
    }
    else if(input == 'd'){
        nextCol ++;
    }
    else if(input == 'u'){
        gameState* prev = undoMoveDo(undoHead);
        if(prev != NULL){
            freeDisplayMap(game->displayMap, game->mapInfo);
            memcpy(game, prev, sizeof(gameState));
            free(prev);
        }
        return;
    }

    if(nextRow >= 0 && nextRow < game->mapInfo->rows && nextCol >= 0 && nextCol < game->mapInfo->cols){
        char destinationTile = game->displayMap[nextRow][nextCol];

        if(destinationTile != 'O' && (destinationTile != 'X' || game->trapTrigger == 0 || game->flooded == 0 || game->goalReached == 0)){
            
            game->displayMap[game->player.row][game->player.col] = ' ';
            game->player.row = nextRow;
            game->player.col = nextCol;
            game->displayMap[game->player.row][game->player.col] = 'P';
            
            
            
            if (destinationTile == 'G')
            {
                game->goalReached = 1;
                game->gameRunning = 0;
            }
            else if (destinationTile == '~'){
                game->flooded = 1;
                game->gameRunning = 0;
            }
            
            if (destinationTile == '@'){
                triggerTrap(game);
            }
            if(game->trapTrigger == 1)
            {
                spreadWater(game);
            }
            
        }
    }
}

void triggerTrap(gameState* game){
    int i, j;
    game->trapTrigger = 1;

    for (i = 0; i < game->mapInfo->rows; i++)
    {
        for (j = 0; j < game->mapInfo->cols; j++)
        {
            if (game->displayMap[i][j] == '@' || game->displayMap[i][j] == 'X')
            {
                game->displayMap[i][j] = ' ';
            }
        }
    }
}

void spreadWater(gameState* game){
    int i, j;
    char** tempMap = (char**)malloc(game->mapInfo->rows * sizeof(char*));
    for(i = 0; i < game->mapInfo->rows; i++)
    {
        tempMap[i] = (char*)malloc(game->mapInfo->cols * sizeof(char));
        for(j = 0; j < game->mapInfo->cols; j++)
        {
            tempMap[i][j] = game->displayMap[i][j];
        }
    }

    for (i = 0; i < game->mapInfo->rows; i++)
    {
        for (j = 0; j < game->mapInfo->cols; j++)
        {
            if (tempMap[i][j] == '~')
            {
                if(i > 0 && tempMap[i-1][j] != 'O' && tempMap[i-1][j] != '~'){
                    game->displayMap[i-1][j] = '~';
                }
                if(i < game->mapInfo->rows - 1 && tempMap[i+1][j] != 'O' && tempMap[i+1][j] != '~'){
                    game->displayMap[i+1][j] = '~';
                }
                if(j > 0 && tempMap[i][j-1] != 'O' && tempMap[i][j-1] != '~'){
                    game->displayMap[i][j-1] = '~';
                }
                if(j < game->mapInfo->cols - 1 && tempMap[i][j+1] != 'O' && tempMap[i][j+1] != '~'){
                    game->displayMap[i][j+1] = '~';
                }
            }
        }
    }
    
    for(i = 0; i < game->mapInfo->rows; i++)
    {
        free(tempMap[i]);
    }
    free(tempMap);
}

Player findPlayer(const gameMapInfo* mapInfo){
    int i, j;
    Player p;
    p.row = 0; 
    p.col = 0;

    for(i = 0; i < mapInfo->rows; i++)
    {
        for(j = 0; j < mapInfo->cols; j++)
        {
            if(mapInfo->mapMatrix[i][j] == 5)
            {
                p.row = i;
                p.col = j;
                return p;
            }
        }
    }
    return p;
}

void printDisplayMap(char** map, const gameMapInfo* mapInfo){
    int i, j;
    for (j = 0; j < mapInfo->cols + 2; j++) { printf("*"); }
    printf("\n");

    for (i = 0; i < mapInfo->rows; i++){
        printf("*");

        for(j = 0; j < mapInfo->cols; j++){
            char currentTile = map[i][j];
            if (currentTile == '~'){
                setBackground("blue"); 
                printf("%c", currentTile); 
                setBackground("reset");
            }
            else if(currentTile == '@'){
                setBackground("red"); 
                printf("%c", currentTile); 
                setBackground("reset");
            }
            else if(currentTile == 'G'){ 
                setBackground("green");
                printf("%c", currentTile);
                setBackground("reset");
            }
            else{
                printf("%c", currentTile);
            }
        }
        printf("*\n");
    }

    for (j = 0; j < mapInfo->cols + 2; j++){
        printf("*");
    }
    printf("\n");
}
#include "gamemech.h"
/* this file contains the main game mechanics functions */

/* this function handles the player inputs and updates the game state accordingly */
/* it takes in the input from the main game loop, the pointer to the current game state which is the struct, and a pointer to the undo stack which is my linked list*/
void handleInput(char input, gameState* game, linkedListNode** undoStack){
    int nextRow = game->player.row; /* next row position of the player */
    int nextCol = game->player.col; /* next column osition of the player */
    /* the following set of conditions determines which direction the player moves in relative to the postion in the array*/
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
    else if(input == 'u'){ /* tihs condition performs the actual undo function*/
        gameState* previousState = (gameState*)removeFirst(undoStack); /* it defines the previous state to be the next item from head in the linked list which is hte current state.*/
        if(previousState != NULL){ /* it checks if the previous state is not null*/
            freeDisplayMap(game->displayMap, game->mapInfo); /* it frees the current display map to avoid memory leaks or dangling pointers*/
            memcpy(game, previousState, sizeof(gameState)); /* it then copies the previous state into the current game state*/
            free(previousState); /* it then frees the previous state to avoid memory leaks*/
        }
        return;
    }
    else{
        return;
    }

    /* this is basicallly my collision management algorithm*/
    /* it checks if the next position is within the bounds of the map and if the destination tile is not an obstacle or water tile*/
    if(nextRow >= 0 && nextRow < game->mapInfo->rows && nextCol >= 0 && nextCol < game->mapInfo->cols){ /* this checks if hte player is within the map bounds*/
        char destinationTile = game->displayMap[nextRow][nextCol]; /* this gets the character at the next position*/
        gameState* currentState; /* this defines a pointer to the current state of the game*/

        if(destinationTile != 'O' && destinationTile != 'X' && (game->trapTrigger == 0 || game->flooded == 0 || game->goalReached == 0)){ /* this checks if the destination tile is not an obstacle or water tile*/
            /* before moving the player, save the current state to the undo stack */
            currentState = (gameState*)malloc(sizeof(gameState));
            memcpy(currentState, game, sizeof(gameState));
            currentState->displayMap = copyDisplayMap(game->displayMap, game->mapInfo->rows, game->mapInfo->cols);
            insertFirst(undoStack, currentState);

            /* update the player's position on the display map by setting the current position to a space and the new position to 'P' */
            game->displayMap[game->player.row][game->player.col] = ' ';
            game->player.row = nextRow;
            game->player.col = nextCol;
            game->displayMap[game->player.row][game->player.col] = 'P';
            
            
            /* check for special tiles and update game state accordingly */
            if (destinationTile == 'G')
            {
                game->goalReached = 1;
                game->gameRunning = 0;
            }
            /* if the player steps on water, the game ends with a flood */
            else if (destinationTile == '~'){
                game->flooded = 1;
                game->gameRunning = 0;
            }
            /* if the player steps on a trap it triggers the trap which removes all traps and obstacles from the map and starts the water spread */
            else
            if (destinationTile == '@'){
                triggerTrap(game);
            }
            if(game->trapTrigger == 1)
            {
                spreadWater(game);
                if (game->displayMap[game->player.row][game->player.col] == '~'){
                    game->flooded = 1;
                    game->gameRunning = 0;
                }
            }
            
        }
    }
}

/* this is a simple function which basically opens the trapgates and replaces them with blank spaces and also removes the trapdoor itself from the map.*/
/* it does it by scanning the entire map (array) using two forloops.*/
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

/* this functions handles the spread of water by using the brute for method as Antoni suggested.*/
void spreadWater(gameState* game){
    int i, j;
    char** tempMap = (char**)malloc(game->mapInfo->rows * sizeof(char*)); /* this creates a temporary map to store the current state of the display map*/
    for(i = 0; i < game->mapInfo->rows; i++) /* this loop deep copies the current state of the display map to the temporary map*/
    {
        tempMap[i] = (char*)malloc(game->mapInfo->cols * sizeof(char));
        for(j = 0; j < game->mapInfo->cols; j++)
        {
            tempMap[i][j] = game->displayMap[i][j];
        }
    }
    /* this set of nested loops scans the entire map and checks for water tiles and spreads the water to adjacent tiles if they are not obstacles or already water tiles*/
    /* it does it by checking adjancent matrix cells on the map relative to each water tile to determine whether it can spread or not and then spreds respectively.*/
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
    /* this frees the temporary map to avoid memory leaks*/
    for(i = 0; i < game->mapInfo->rows; i++)
    {
        free(tempMap[i]);
    }
    free(tempMap);
}

/* this function finds the player in the map by scanning the entire map using two for loops and checking for the player tile which is 5 in the map matrix*/
Player findPlayer(const gameMapInfo* mapInfo){
    int i, j;
    Player p;
    p.row = -1; /* I decided to set the initial values of the player to -1,-1 to avoid any issue in the event that 0,0 on another map is a trap or something else*/
    p.col = -1;

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

/* this function prints the display map to the console with a border of asterisks and also adds color to certain tiles as per the provided sample output in the assignment brief*/
/* if uses the provided colour file to set the colours.*/
void printDisplayMap(char** map, const gameMapInfo* mapInfo){
    int i, j;
    for (j = 0; j < mapInfo->cols + 2; j++) { printf("*"); }
    printf("\n");

    for (i = 0; i < mapInfo->rows; i++){ /* this prints each row of the map with asterisks on the sides*/
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

    for (j = 0; j < mapInfo->cols + 2; j++){ /* this prints horizontal border of asterisks*/
        printf("*");
    }
    printf("\n");
}
#include "escape.h"

int main(int argc, char *argv[]){
    gameState game;
    char input = ' ';
    linkedListNode* undoStack = NULL;
    game.gameRunning = 1;

    game.gameRunning = 1;
    game.flooded = 0;
    game.goalReached = 0;

    if (argc != 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }
    
    game.mapInfo = importMap(argv[1]);
    if (game.mapInfo == NULL){ 
        return 1;
    }

    game.displayMap = createGameMap(game.mapInfo);
    if (game.displayMap == NULL){
        freeMapData(game.mapInfo); 
        return 1;
    }

    game.player = findPlayer(game.mapInfo);
    game.trapTrigger = 0;

    disableBuffer();
    while(game.gameRunning == 1 && game.flooded == 0 && game.goalReached == 0)
    {
        system("clear");
        printf("UCP 2025 Semester Two - Assignment - Escape the Flood!\n");
        printDisplayMap(game.displayMap, game.mapInfo);
        printf("\nPress 'w' to move UP\nPress 's' to move DOWN\nPress 'a' to move LEFT\nPress 'd' to move RIGHT\n");
        printf("Press 'u' to UNDO.\n");
        
        input = getchar();

        handleInput(input, &game, &undoStack);
    }
    enableBuffer();

    system("clear");
    printDisplayMap(game.displayMap, game.mapInfo);
    if(game.goalReached == 1){
        printf("Congratulations! You've reached the goal!\n");
    }
    else if(game.flooded == 1){
        printf("Game Over! You've been flooded!\n");
    }


    freeList(&undoStack, freeGameState);
    freeDisplayMap(game.displayMap, game.mapInfo);
    freeMapData(game.mapInfo);
    return 0;
}

char** copyDisplayMap(char** map, int rows, int cols){
    int i;
    char** newMap = (char**)malloc(rows * sizeof(char*));
    for(i = 0; i < rows; i++){
        newMap[i] = (char*)malloc(cols * sizeof(char));
        memcpy(newMap[i], map[i], cols * sizeof(char));
    }
    return newMap;
}

void freeGameState(void* data){
    gameState* state = (gameState*)data;
    if (state != NULL){
        freeDisplayMap(state->displayMap, state->mapInfo);
        free(state);
    }
}



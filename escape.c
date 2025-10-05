#include "escape.h"

int main(int argc, char *argv[]){
    gameState game;
    char input = ' ';
    undoNode* undoHead = NULL;

    game.gameRunning = 1;

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
        freeMapData(game.mapInfo); return 1;
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
        
        if(input != 'u'){
            undoMoveStore(&undoHead, &game);
        }

        input = getchar();

        handleInput(input, &game, &undoHead);
    }

    system("clear");
    printDisplayMap(game.displayMap, game.mapInfo);
    if(game.goalReached == 1){
        printf("Congratulations! You've reached the goal!\n");
    }
    else if(game.flooded == 1){
        printf("Game Over! You've been flooded!\n");
    }

    enableBuffer();

    freeDisplayMap(game.displayMap, game.mapInfo);
    freeMapData(game.mapInfo);
    return 0;
}

char** deepCopyDisplayMap(char** src, int rows, int cols) {
    int i;
    char** dest = malloc(rows * sizeof(char*));
    for (i = 0; i < rows; i++) {
        dest[i] = malloc(cols * sizeof(char));
        memcpy(dest[i], src[i], cols * sizeof(char));
    }
    return dest;
}

void undoMoveStore(undoNode** head, gameState* game){
    undoNode* newNode = malloc(sizeof(undoNode));
    gameState* snapshot = malloc(sizeof(gameState));
    memcpy(snapshot, game, sizeof(gameState));
    snapshot->displayMap = deepCopyDisplayMap(game->displayMap, game->mapInfo->rows, game->mapInfo->cols);
    newNode->data = snapshot;
    newNode->next = *head;
    *head = newNode;
}
gameState* undoMoveDo(undoNode** head){
    undoNode* temp; 
    gameState* snapshot; 
    if (*head == NULL){
        return NULL;
    }
    temp = *head;
    snapshot = temp->data;
    *head = temp->next;
    free(temp);
    return snapshot;
}




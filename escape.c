#include "escape.h"

/* Escape.c : This file is essentially my main file that gets compiled into the actual program*/
/* Functions: main: the main function is run which then calls all of the other respective functions to run the game.*/
/* copyDisplayMap: creates a copy of the current display map for undo functionality.*/
/* freeGameState: frees the memory allocated for a gameState struct.*/

int main(int argc, char *argv[]){
    gameState game; /* Main game state struct that stores current game state info such as game running status, flooding status, trapdoor status, goal status, player status (called from the player struct) etc.*/
    char input = ' '; /* Variable to store user input*/
    linkedListNode* undoStack = NULL; /* Linked list stack to store previous game states for undo functionality */
    
    /* defines the initial game state values*/
    game.flooded = 0;
    game.gameRunning = 1; 
    game.goalReached = 0; 

    if (argc != 2) /* checks if the number of command line arguments is correct i.e., 2 (program name and map file path) */
    {
        printf("Usage: %s <map_file>\n", argv[0]); /* if the number of arguments is not correct i.e, map directory is not inputted, then it prints what the program expects from the user (map path)*/
        return 1;
    }
    
    game.mapInfo = importMap(argv[1]); /* calls the importMap function from fileimport.c which is responsible for interpreting the map text file, mallcoing the memory and storing the game map. and stores in the gameState struct */
    if (game.mapInfo == NULL){ 
        return 1; /* if the mapInfo in teh gameState struct is null then the program returns 1 and ends.*/
    }
    
    /*The display map is what the usuer will actually see as it renders the map with borders, and the respective colours.*/
    game.displayMap = createGameMap(game.mapInfo);
    if (game.displayMap == NULL){
        freeMapData(game.mapInfo); /* if the displayMap in the struct is null it will free the allocated memory for it before returning 1 and exiting to avoid memory leaks.*/
        return 1;
    }
    
    game.player = findPlayer(game.mapInfo); /* finds the player position in the map and stores it in the gameState struct which has a player struct which stores the player postion*/
    game.trapTrigger = 0; /* defines the trap trigger to zero.*/
    
    disableBuffer(); /* disables the terminal input buffer so that the user does not have to press enter after every input*/

    /* this is the main game loop which checks for the correct game state conditions before letting the game run*/
    while(game.gameRunning == 1 && game.flooded == 0 && game.goalReached == 0)
    {
        system("clear"); /* clears the terminals based on Antoni's easy suggestion to print the next move without moving the terminal window.*/
        printf("UCP 2025 Semester Two - Assignment - Escape the Flood!\n");
        printDisplayMap(game.displayMap, game.mapInfo); /* this function actually prints the display map using the data stored in the displayMap in the gameState struct and the info from the mapInfo which contains no. of rows and cols as well as the numerical matrix from the import.*/
        printf("\nPress 'w' to move UP\nPress 's' to move DOWN\nPress 'a' to move LEFT\nPress 'd' to move RIGHT\n");
        printf("Press 'u' to UNDO.\n");
        
        input = getchar(); /* gets the user key input*/

        handleInput(input, &game, &undoStack); /* This parses the user input, the address to the gameStruct, and the linkedListNode struct and handles the player movement (incl. boundaries), storing the previous game state for hte linked list etc.*/
    }
    enableBuffer(); /* re-enables the terminal input buffer after the game loop ends*/

    /* I ran into an issue where the game did not render the final player move i.e., getting flooded or stepping on the goal, this fixes it by rendering the final move once the quit conditions are met.*/
    system("clear");
    printDisplayMap(game.displayMap, game.mapInfo);

    /* basically checks the end conditions and then prints the outputs based on whether the player is flooded or they reach the goal*/
    if(game.goalReached == 1){
        printf("Congratulations! You've reached the goal!\n");
    }
    else if(game.flooded == 1){
        printf("Game Over! You've been flooded!\n");
    }

    /* frees all of the malloced memory from the maps, linked lists etc. to avoid Antoni's Nightmare (memory leaks)*/
    freeList(&undoStack, freeGameState);
    freeDisplayMap(game.displayMap, game.mapInfo);
    freeMapData(game.mapInfo);
    return 0;
}

/* This function copies the display map for it to be stored in the linkedlist for the undo functionality. I should probably have declared it in my gamemech.c file but oh well its in the header and called there.*/
char** copyDisplayMap(char** map, int rows, int cols){
    int i;
    /* this allocated the memory of the map that will be deepcopied*/
    char** newMap = (char**)malloc(rows * sizeof(char*));
    /*this loop actually does the deep copy*/
    for(i = 0; i < rows; i++){
        newMap[i] = (char*)malloc(cols * sizeof(char));
        memcpy(newMap[i], map[i], cols * sizeof(char));
    }
    /* returns the map */
    return newMap;
}
/* this function frees the gameState struct that is passed to it as a void pointer from the linked list free function*/
void freeGameState(void* data){
    gameState* state = (gameState*)data; /* casts the void pointer to a gameState struct pointer*/
    /* if the state is not null it frees the display map and the gameState struct itself*/
    if (state != NULL){
        freeDisplayMap(state->displayMap, state->mapInfo);
        free(state);
    }
}



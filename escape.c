#include "escape.h"
#include "terminal.h"

void printDisplayMap(char** map, const gameMapInfo* mapInfo);
Player findPlayer(const gameMapInfo* mapInfo);
void handleInput(char input, gameState* game);
void triggerTrap(gameState* game);
void spreadWater(gameState* game);

int main(int argc, char *argv[])
{
    gameState game;
    char input = ' ';
    int gameRunning = 1;

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
    while(gameRunning)
    {
        printf("\033[2J\033[H");
        printDisplayMap(game.displayMap, game.mapInfo);
        printf("\nControls: 'w' (up), 's' (down), 'a' (left), 'd' (right)\n");
        printf("Press 'q' to quit.\n");
        
        input = getchar();

        if (input == 'q')
        {
            gameRunning = 0;
        }
        else
        {
            handleInput(input, &game);
        }
    }
    enableBuffer();
    
    printf("Game Over!\n");
    freeDisplayMap(game.displayMap, game.mapInfo);
    freeMapData(game.mapInfo);
    return 0;
}

void handleInput(char input, gameState* game)
{
    int nextRow = game->player.row;
    int nextCol = game->player.col;

    switch(input)
    {
        case 'w': nextRow--; break;
        case 's': nextRow++; break;
        case 'a': nextCol--; break;
        case 'd': nextCol++; break;
    }
    
    if(nextRow >= 0 && nextRow < game->mapInfo->rows && nextCol >= 0 && nextCol < game->mapInfo->cols)
    {
        char destinationTile = game->displayMap[nextRow][nextCol];

        if(destinationTile != 'O' && (destinationTile != 'X' || game->trapTrigger))
        {
            if (destinationTile == '@')
            {
                triggerTrap(game);
            }

            game->displayMap[game->player.row][game->player.col] = ' ';
            game->player.row = nextRow;
            game->player.col = nextCol;
            game->displayMap[game->player.row][game->player.col] = 'P';

            if(game->trapTrigger)
            {
                spreadWater(game);
            }
        }
    }
}

void triggerTrap(gameState* game)
{
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

void spreadWater(gameState* game)
{
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
                if (i > 0 && tempMap[i-1][j] != 'O' && tempMap[i-1][j] != '~')
                    game->displayMap[i-1][j] = '~';
                if (i < game->mapInfo->rows - 1 && tempMap[i+1][j] != 'O' && tempMap[i+1][j] != '~')
                    game->displayMap[i+1][j] = '~';
                if (j > 0 && tempMap[i][j-1] != 'O' && tempMap[i][j-1] != '~')
                    game->displayMap[i][j-1] = '~';
                if (j < game->mapInfo->cols - 1 && tempMap[i][j+1] != 'O' && tempMap[i][j+1] != '~')
                    game->displayMap[i][j+1] = '~';
            }
        }
    }
    
    for(i = 0; i < game->mapInfo->rows; i++)
    {
        free(tempMap[i]);
    }
    free(tempMap);
}

Player findPlayer(const gameMapInfo* mapInfo)
{
    int i, j;
    Player p;
    p.row = -1; 
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

void printDisplayMap(char** map, const gameMapInfo* mapInfo)
{
    int i, j;
    for (j = 0; j < mapInfo->cols + 2; j++) { printf("*"); }
    printf("\n");

    for (i = 0; i < mapInfo->rows; i++)
    {
        printf("*");
        for(j = 0; j < mapInfo->cols; j++)
        {
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


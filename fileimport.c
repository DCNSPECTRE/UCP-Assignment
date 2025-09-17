#include "fileimport.h"

int** importMap(const char* filepath){

    const char* fileName = filepath;

    /*Defines a file pointer, and then defines the value of the file pointer */
    const char * fileName = argv[1];
    filePtr = fopen(fileName, "r");

    /*If the pointer to the file is null, then it returns an error.*/
    if(filePtr == NULL){
        printf("Error openiing file!\n");
        return 1;
    }

    printf("File '%s' opened.\n\n Creating Array...", fileName);

    /*Define the integers required to make a 2D malloc'd array*/

    int r, c, i;

    /*The above defined integers are assigned a value from the first two numbers in the map file*/

    fscanf(filePtr, "%d %d", &r, &c);

    /*Allocation of the first dimension of the array*/
    int ** mapMatrix = malloc(r * sizeof(int*));
    
    /*Allocation of the second dimension of the file*/
    for(i = 0; i < r; i++){
        mapMatrix[i] = malloc(c * sizeof(int));
    }

    printf("Array Created with Dimensions ('%d' x '%d'). Map Generation in Progress.\n", r, c);
    
    /*Assigning each value of the array with a value from the map file*/
    int j;
    for(i = 0; i < r; i++){
        for(j = 0; j < c; j++){
            fscanf(filePtr, "%d", &mapMatrix[i][j]);
        }
    }
    printf("Map Generation Completed.\n");

    fclose(filePtr)
    /*Returns the address to the map matrix*/
    return mapMatrix;
}

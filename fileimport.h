#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "color.h"

typedef struct{
    int rows;
    int cols;
    int ** mapMatrix;
}gameMapInfo;
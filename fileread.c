#include <stdio.h>
#include <stdlib.h>
#include "fileread.h"

/*function to interpret the incoming data from the file*/
void getMapdata(int *** mapTable, int * dataAmount, int * mapRow, int * mapCol, FILE* f)
{
    int i;
    int j;
    int ** table;

    /*scans first line for the amount of data and the size of the map*/
    fscanf(f, "%d %d %d", dataAmount, mapRow, mapCol);

    /*creation of the map table*/
    table = (int **) malloc(sizeof(int *) * (*dataAmount));

    for(i = 0 ; i < (*dataAmount) ; i++)
    {
        table[i] = (int *) malloc(sizeof(int) * 3);
    }

    for(i = 0; i < *dataAmount; i++)
    {
        for(j = 0; j < 3; j++)
        {
            fscanf(f, "%d", &table[i][j]);
        }
    }

    *mapTable = table;
}
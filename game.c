#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileread.h"
#include "game.h"

/* funtion that generates initial map from metadata */
void generateMap(char *** map, int * outrows, int * outcols, posNode * entityPos, FILE* f)
{
    int ** metadata;
    int dataAmount;
    int rows;
    int cols;

    int i;

    char ** mapArray;

    getMapdata(&metadata, &dataAmount, &rows, &cols, f);

    *outrows = rows;
    *outcols = cols;
    
    /* creating an array to build the map on */
    mapArray = (char **) malloc(sizeof(char *) * (rows));

    for (i = 0; i < rows; i++)
    {
        mapArray[i] = (char *) malloc(sizeof(char) * (cols));
        memset(mapArray[i], ' ', sizeof(char) * (cols));
    }

    /* setting up map border */
    mapArray[0][0] = '#';
    mapArray[0][cols - 1] = '#';
    mapArray[rows - 1][0] = '#';
    mapArray[rows - 1][cols - 1] = '#';

    for (i = 1; i < rows - 1; i++)
    {
        mapArray[i][0] = '|';
        mapArray[i][cols - 1] = '|';
    }
    for (i = 1; i < cols - 1; i++)
    {
        mapArray[0][i] = '-';
        mapArray[rows - 1][i] = '-';
    }

    /* placing objects into their starting positions */
    for (i = 0; i < dataAmount; i++)
    {
        int mrow = metadata[i][0];
        int mcol = metadata[i][1];

        /* setting position of the player */
        if (metadata[i][2] == 0) 
        {
            mapArray[mrow][mcol] = '^';
            entityPos->playerIcon = '^';
            entityPos->playerRow = metadata[i][0];
            entityPos->playerCol = metadata[i][1];
        }

        /* setting position of the snake */
        if (metadata[i][2] == 1) 
        {
            mapArray[mrow][mcol] = '~';
            entityPos->snakeRow = metadata[i][0]; 
            entityPos->snakeCol = metadata[i][1]; 
        }

        /* setting position of the exit */
        if (metadata[i][2] == 2) 
        {
            mapArray[mrow][mcol] = 'x';
        }

        /* setting position of the obsticles */
        if (metadata[i][2] == 3) 
        {
            mapArray[mrow][mcol] = 'o';
        }
    } 

    *map = mapArray;

    /* frees metadata array after the map is generated */
    for (i = 0; i < dataAmount; i++) 
    {
        free(metadata[i]);
        metadata[i] = NULL;
    }
    free(metadata);
    metadata = NULL; 
} 

/* funtion that prints the map to terminal and changes visibility conditions */
void printMap(char ** map, int rows, int cols)
{
    int i;
    int j;

    /* printing mapArray */
    for(i = 0; i < rows; i++) 
    { 
        for(j = 0; j < cols; j++) 
        {
            printf("%c", map[i][j]);
        }
        printf("\n"); 
    }
 
}

/*function that determines the movement of the player*/
void pMovement(char *** map, posNode * playerPos, int * checkWin, char playerInput)
{
    char ** mapArray = *map;
    int prow = playerPos->playerRow;
    int pcol = playerPos->playerCol;
    char pIcon = playerPos->playerIcon;

    /*  the following moves the player icon depending on user input 
        the cases for 's', 'a' and 'd' function exactly the same as 'w' just with different conditions */
    if (playerInput == 'w')
    {
        mapArray[prow][pcol] = '^'; /* turns player even if player cannot move */
        pIcon = '^';
        if (mapArray[prow - 1][pcol] == 'x') /* activates win condition upon moving to x */
        {
            *checkWin = 1;
        }
        if (mapArray[prow - 1][pcol] != 'o' && mapArray[prow - 1][pcol] != '-') /* checks for barriers */
        {
            mapArray[prow][pcol] = ' ';
            prow -= 1;
            mapArray[prow][pcol] = '^';
            pIcon = '^';
        }
    }
    if (playerInput == 's')
    {
        mapArray[prow][pcol] = 'v';
        pIcon = 'v';
        if (mapArray[prow + 1][pcol] == 'x')
        {
            *checkWin = 1;
        }
        if (mapArray[prow + 1][pcol] != 'o' && mapArray[prow + 1][pcol] != '-')
        {
            mapArray[prow][pcol] = ' ';
            prow += 1;
            mapArray[prow][pcol] = 'v';
            pIcon = 'v';
        }
    }
    if (playerInput == 'a')
    {
        mapArray[prow][pcol] = '<';
        pIcon = '<';
        if (mapArray[prow][pcol - 1] == 'x')
        {
            *checkWin = 1;
        }
        if (mapArray[prow][pcol - 1] != 'o' && mapArray[prow][pcol - 1] != '|')
        {
            mapArray[prow][pcol] = ' ';
            pcol -= 1;
            mapArray[prow][pcol] = '<';
            pIcon = '<';
        }
    }
    if (playerInput == 'd')
    {
        mapArray[prow][pcol] = '>';
        pIcon = '>';
        if (mapArray[prow][pcol + 1] == 'x')
        {
            *checkWin = 1;
        }
        if (mapArray[prow][pcol + 1] != 'o' && mapArray[prow][pcol + 1] != '|')
        {
            mapArray[prow][pcol] = ' ';
            pcol += 1;
            mapArray[prow][pcol] = '>';
            pIcon = '>';
        }
    }
    /* re-assigns new player positions for next iteration */
    playerPos->playerRow = prow;
    playerPos->playerCol = pcol;
    playerPos->playerIcon = pIcon;
}

/*function that determines the movement of the snake*/
void sMovement(char *** map, posNode * entityPos, int * checkLose)
{
    char ** mapArray = *map;
    int prow = entityPos->playerRow;
    int pcol = entityPos->playerCol;
    int srow = entityPos->snakeRow;
    int scol = entityPos->snakeCol;

    /*absolute distance between the player and snake*/
    int distRow = abs(srow - prow);
    int distCol = abs(scol - pcol);

    /*movement essentially works the same way as in pMovement but is instead triggered by the
        current position of the player*/
    if (distRow < distCol) /*stops their from being conflict between which axis the snake moves in*/
    {
        if (scol < pcol) 
        {
            if (mapArray[srow][scol + 1] != 'o' && mapArray[srow][scol + 1] != '|' && mapArray[srow][scol + 1] != 'x') 
            {
                mapArray[srow][scol] = ' ';
                scol += 1;
                mapArray[srow][scol] = '~';
            }
        }
        if (scol > pcol)
        {
            if (mapArray[srow][scol - 1] != 'o' && mapArray[srow][scol - 1] != '|' && mapArray[srow][scol - 1] != 'x') 
            {
                mapArray[srow][scol] = ' ';
                scol -= 1;
                mapArray[srow][scol] = '~';
            }
        }
    }
    else 
    {
        if (srow < prow) 
        {
            if (mapArray[srow + 1][scol] != 'o' && mapArray[srow + 1][scol] != '|' && mapArray[srow + 1][scol] != 'x') 
            {
                mapArray[srow][scol] = ' ';
                srow += 1;
                mapArray[srow][scol] = '~';
            }
        }
        if (srow > prow)
        {
            if (mapArray[srow - 1][scol] != 'o' && mapArray[srow - 1][scol] != '|' && mapArray[srow - 1][scol] != 'x') 
            {
                mapArray[srow][scol] = ' ';
                srow -= 1;
                mapArray[srow][scol] = '~';
            }
        }
    }

    if (srow == prow && scol == pcol) 
    {
        *checkLose = 1;
    }
    /* re-assigns new snake positions for next iteration */
    entityPos->snakeRow = srow;
    entityPos->snakeCol = scol;
}

/*fuction for inserting a new node at the begining of the linked list*/
posNode * insertNode(posNode * entityPos, posNode * head) 
{
    posNode * newNode;

    newNode = (posNode*)malloc(sizeof(posNode));
    newNode->playerRow = entityPos->playerRow;
    newNode->playerCol = entityPos->playerCol;
    newNode->snakeRow = entityPos->snakeRow;
    newNode->snakeCol = entityPos->snakeCol;
    newNode->playerIcon = entityPos->playerIcon;
    newNode->next = NULL; /*not nessicary but redundancy never hurts*/

    newNode->next = head;
    head = newNode;
    return head;
}

/*fuction for freeing the linked list*/
void freeList(posNode * head) 
{
    posNode * copyNode;

    while(head != NULL) 
    {
        copyNode = head;
        head = head->next;
        free(copyNode);
        copyNode = NULL;
    }
}
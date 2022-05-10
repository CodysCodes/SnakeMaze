#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
#include "game.h"

int main(int argc, char * argv[]) 
{
    /* dimentions of game map */
    int rows;
    int cols;

    /* declaring the variables for the linked list */
    posNode * head = NULL;
    posNode * currentPos;
    posNode * copyNode;

    char ** map;
    char playerInput;

    int i;

    int checkWin = 0; 
    int checkLose = 0;

    if (argc > 1) /* checks if the number of arguments is large enough */
    {
        if (argc < 3) /* checks if the number of arguments too large */
        {
            FILE* f = fopen(argv[1],"r");
            if (f == NULL) 
            {
                perror("Error opening file");
            }
            else 
            {
                /* allocates memory to the head and generates all map values */
                head = (posNode*)malloc(sizeof(posNode));
                generateMap(&map, &rows, &cols, head, f);
                head->next = NULL;
                currentPos = head;

                /* reprints game while the win and lose conditions remains 0 */
                while (checkWin == 0 && checkLose == 0)
                {
                    head = insertNode(currentPos, head);
                    system("clear");

                    printMap(map, rows, cols);

                    disableBuffer();
                    scanf("%c", &playerInput);
                    enableBuffer();

                    /* checks if an 'undo' can be performed, if not the game will play as usual */
                    if (playerInput == 'u' && currentPos!= NULL)
                    {
                        if (currentPos->next !=NULL)
                        {
                            /* removing current player and snake icons */
                            map[currentPos->playerRow][currentPos->playerCol] = ' ';
                            map[currentPos->snakeRow][currentPos->snakeCol] = ' ';

                            /* replaces the current and head with their previous state */
                            copyNode = head;
                            head = head->next;
                            currentPos = currentPos->next;
                            free(copyNode);

                            /* replacing player and snake icons in their previous positions */
                            map[currentPos->playerRow][currentPos->playerCol] = currentPos->playerIcon;
                            map[currentPos->snakeRow][currentPos->snakeCol] = '~';
                        }
                    }
                    else
                    {
                        currentPos = head;
                        pMovement(&map, currentPos, &checkWin, playerInput);
                        sMovement(&map, currentPos, &checkLose);
                    }
                }
                /* prints map one last time so players can see their final positions */
                system("clear");
                printMap(map, rows, cols);

                if (checkWin == 1) 
                {
                    printf("\nYou Win!\n");
                } 
                else 
                {
                    printf("\nYou Lose :(\n");
                }

                freeList(head);

                /* frees the map array after game is complete */
                for (i = 0; i < rows; i++) 
                {
                    free(map[i]);
                    map[i] = NULL;
                }
                free(map);
                map = NULL;

                fclose(f);
            }
        }
        else
        {
            printf("\nToo many arguments!\n");
        }
    }
    else 
    {
        printf("\nToo few arguments!\n");
    }

    return 0;
}
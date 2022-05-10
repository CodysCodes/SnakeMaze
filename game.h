#ifndef GAME_H
#define GAME_H

/*declearation of the linked list struct*/
typedef struct Node {
    int playerRow;
    int playerCol;
    int snakeRow;
    int snakeCol;
    char playerIcon;
    struct Node * next;
} posNode;

void generateMap(char *** map, int * outrows, int * outcols, posNode * entityPos, FILE* f);
void printMap(char ** map, int nrows, int ncols);
void pMovement(char *** map, posNode * entityPos, int * checkWin, char playerInput);
void sMovement(char *** map, posNode * entityPos, int * checkLose); 
posNode * insertNode(posNode * entityPos, posNode * head);
void freeList(posNode * head);

#endif